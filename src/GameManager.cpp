#include "../include/GameManager.hpp"
#include "../include/Bishop.hpp"
#include "../include/Exceptions.hpp"
#include "../include/King.hpp"
#include "../include/Knight.hpp"
#include "../include/Pawn.hpp"
#include "../include/Queen.hpp"
#include "../include/Rook.hpp"
#include "../include/User.hpp"
#include "Functions.cpp"
#include <ctime>
#include <random>

#include <stdexcept>
#include <QDebug>

using namespace std;

GameManager *GameManager::game_manager = nullptr;

//_______________________________________________________________________________________________________ get

GameManager *&GameManager::get(GameName name)
{
    if (game_manager == nullptr)
        game_manager = new GameManager(name);

    return game_manager;
}

//_______________________________________________________________________________________________________ load game
//-----------------------// sets game data

void GameManager::loadGame(std::string gameName)
{
    fileManager.readFile(gameName, false);

    qDebug() << "---------------- loading file...";
    string name1 = fileManager.get_P1_Name(), name2 = fileManager.get_P2_Name().c_str();

    this->setTurn(Turn::USER1);

    this->game_name = gameName;
    this->users[0] = User::get(name1, Chessman::Color::WHITE, 0, 0);
    getUser1()->setColor(Chessman::Color::WHITE);
    getUser1()->setChessmansIn();

    this->users[1] = User::get(name2, Chessman::Color::WHITE, 0, 0);
    getUser2()->setColor(Chessman::Color::BLACK);
    getUser2()->setChessmansIn();

    startGame();

    qDebug() << "user1: " << users[0]->getName().c_str() << users[0]->getColor();
    for (auto item : users[0]->getChessmansIn())
        qDebug() << item->getID().c_str();

    qDebug() << "user2: " << users[1]->getName().c_str() << users[1]->getColor();
    for (auto item : getUser2()->getChessmansIn())
        qDebug() << item->getID().c_str();

    this->loadMoves();
}

//________________________________________________________________________________________________________ GameManager

GameManager::GameManager(GameName game_name)
{
    //    setGameName(game_name);
}

//________________________________________________________________________________________________________ Distructor

GameManager::~GameManager()
{
  if(users[0] != nullptr)
  {
    delete users[0];
    users[0] = nullptr;
  }
  if(users[1] != nullptr)
  {
    delete users[1];
    users[1] = nullptr;
  }

  if(chess_board != nullptr)
  {
    delete chess_board;
    chess_board = nullptr;
  }

  chess_board = nullptr;
}

//________________________________________________________________________________________________________ startGame

void GameManager::startGame()
{
    if (users[0] == nullptr || users[1] == nullptr)
        throw runtime_error("All user not seted.");

    setChessBoardGame(ChessBoard::get(users[0], users[1]));
}

//________________________________________________________________________________________________________ getCellState

pair<vector<Chessman::Index>, vector<Chessman::Index>> GameManager::getCellState(
                                                                    Chessman::Index index)
{
    if (chess_board->getCell(index).getChessPieces() == nullptr) // Check in this home has chessman
        throw EmptySquare("In this home any chessman not founded.");

    if (turn == USER1) {
        if (chess_board->getCell(index).getChessPieces()->getColor() == Chessman::BLACK)
            throw AccessDenied("User1 can't selected Black Chessman");
    } else {
        if (chess_board->getCell(index).getChessPieces()->getColor() == Chessman::WHITE)
            throw AccessDenied("User2 can't selected White Chessman");
    }
  auto tempCellState = chess_board->getCanGo(index, true, enpasan);

  //  _______________________________ remvoe dublicated values
  tempCellState.first.erase(unique(tempCellState.first.begin(), tempCellState.first.end()),
                            tempCellState.first.end());
  tempCellState.second.erase(unique(tempCellState.second.begin(), tempCellState.second.end()),
                             tempCellState.second.end());

  //  ___________________________________________ limit checkable moves
  //  qDebug() << "-------------- canGo before limitation" << tempCellState.first;

  limit_cells_for_king_check(index, tempCellState.first, tempCellState.second);

  //  qDebug() << "-------------- canGo after limitation" << tempCellState.first;

  return tempCellState;
}

//_______________________________________________________________________________________________ checkMove

void GameManager::checkMove(Chessman::Index src, Chessman::Index dest)
{
    if (src != dest) {
        if (!chess_board->getCell(src).isFull())
            throw invalid_argument("no chessman selected (check)");

        //---------------------------------------------------- if wants to hit king
        if (chess_board->getCell(dest).isFull())
            if (chess_board->getCell(dest).getChessPieces()->getChessType() == Chessman::KING)
                throw ImpossibleHitKing("King can't be hited");

        //_____________________________________________________ Promotion
        if ((dest.first == 0 || dest.first == 7))
            if (chess_board->getCell(src).getChessPieces()->getChessType()
                == Chessman::ChessType::PAWN)
                throw FinalCellForPawn("Pawn moved to final cell");
    }
}

//________________________________________________________________________________________________________

void GameManager::setMove(Chessman::Index src, Chessman::Index dest, bool in_undo, bool isTemp)
{
    if (src != dest) {
        if (!chess_board->getCell(src).isFull())
            throw invalid_argument("no chessman selected (set)");

        //---------------- calculate score
        User::Score temp_score = 0;

        if (!in_undo && !isTemp) {
            temp_score = calucateScoreMovePiece(src, dest);
            users[turn]->incScore(temp_score);
        }

        string temp_movement;

        //_____________________________________________________ check en-passnat
        if ((turn == USER2)
            && ((src.first == 1 && dest.first == 3) || (src.first == 4 && dest.first == 3)))
            allowEnpasan(dest);

        else if (turn == USER1
                 && ((src.first == 6 && dest.first == 4) || (src.first == 3 && dest.first == 4)))
            allowEnpasan(dest);

        else
            notAllowEnpasan();

        //------------------------- set en-passant mode
        if (enpasan.first == 100 && enpasan.second == 100)
            temp_movement += "NE";
        else
            temp_movement += "AE";

        //------------------ movement index
        temp_movement += to_string(dest.first) + to_string(dest.second) + "%";
        temp_movement += convertOrderToString(src, dest);

        //____________________________________________________________________________ king-rook move

        if (chess_board->getCell(src).isFull()) {
            if (chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::KING
                && in_undo == false)

            {
                //right king-rook
                if (dest.second - src.second == 2) {
                    checkMove(make_pair(dest.first, dest.second + 1),
                              make_pair(dest.first, dest.second - 1));
                    qDebug() << "performing rook move right";
                    setMove(make_pair(dest.first, dest.second + 1),
                            make_pair(dest.first, dest.second - 1),
                            in_undo);
                    temp_movement = "KRO" + temp_movement + " #";
                }

                //left king-rook
                else if (src.second - dest.second == 2) {
                    checkMove(make_pair(dest.first, dest.second - 2),
                              make_pair(dest.first, dest.second + 1));
                    qDebug() << "performing rook move left";
                    setMove(make_pair(dest.first, dest.second - 2),
                            make_pair(dest.first, dest.second + 1),
                            in_undo);

                    temp_movement = "KRO" + temp_movement + " #";
                }
            }
        }

        //_________________________________________________________ move chessman
        pair<Chessman::ID, Chessman::ID> temp = chess_board->moveChessman(src, dest);

        //----------------------- if has hitted a chessman
        if (temp.first != "") {
            if (turn == USER1) // move chessman from chessmans_in to chessmans_out in user class
                users[1]->hitChessman(temp.first);
            else
                users[0]->hitChessman(temp.first);
        }
        //___________________________________________________________ en-passant move
        if (temp.second != "") {
            string temp_movement_ENP = "ENP%" + chess_board->getCell(dest).getChessPieces()->getID()
                                       + " ";
            temp_movement_ENP += to_string(src.first) + to_string(src.second);
            if (turn == USER1) // move chessman from chessmans_in to chessmans_out in user class
            {
                temp_movement_ENP += to_string(dest.first);
                users[1]->hitChessman(temp.second);
            } else {
                temp_movement_ENP += to_string(dest.first);
                users[0]->hitChessman(temp.second);
            }

            //_____________________________________________________ save move
            temp_movement_ENP += to_string(dest.second) + " " + temp.second + "^$"
                                 + to_string(temp_score);
            if (!in_undo && (movements.empty() ? true : temp_movement_ENP != movements.top())) {
                if (!isTemp) {
                    qDebug() << "enp move: " << (temp_movement_ENP).c_str();
                    this->fileManager.saveMove(temp_movement_ENP);
                }
                movements.push(temp_movement_ENP);
                return;
            }
        }

        // if chessman that moved is king or rook moved for it chessman inserted true
        //(king must be at the beggining cell)
        shared_ptr<Chessman> temp_chess = chess_board->getCell(dest).getChessPieces();
        if (temp_chess->getChessType() == Chessman::KING)
            dynamic_cast<King *>(temp_chess.get())->kingMoved();
        else if (temp_chess->getChessType() == Chessman::ROOK)
            dynamic_cast<Rook *>(temp_chess.get())->rookMoved();

        //_____________________________________________________ save move in stack
        auto tempMove = temp_movement + "$" + to_string(temp_score);

        if (!in_undo && (movements.empty() ? true : tempMove != movements.top())) {
            if (!isTemp) {
                qDebug() << "movement: " << tempMove.c_str();
                this->fileManager.saveMove(tempMove);
            }
            movements.push(tempMove);
        }

        //_____________________________________________________ check check
        if (!in_undo && isTemp && isKingChecked())
            throw KingIsChecked("_____________king is checked");
    }
}

//________________________________________________________________________________________________________ setUser1

void GameManager::setUser1(User::Name user1_name, User::Score user1_Pscore, User::Score user1_Nscore)
{
    this->users[0] =  User::get(user1_name, User::Color::WHITE, user1_Pscore, user1_Nscore);
    this->fileManager.set_P1_Name(users[0]->getName());
}

//________________________________________________________________________________________________________ setUser2

void GameManager::setUser2(User::Name user2_name, User::Score user2_Pscore, User::Score user2_Nscore)
{
    this->users[1] = User::get(user2_name, User::Color::BLACK, user2_Pscore, user2_Nscore);
    this->fileManager.set_P2_Name(users[1]->getName());
}

//________________________________________________________________________________________________________ getUser1

GameManager::GameUser GameManager::getUser1() const
{
  return users[0];
}

//________________________________________________________________________________________________________ getUser2

GameManager::GameUser GameManager::getUser2() const
{
  return users[1];
}

//________________________________________________________________________________________________________ setChessBoardGame

void GameManager::setChessBoardGame(const ChessBoardGame &chess_board)
{
  this->chess_board = chess_board;
}

//________________________________________________________________________________________________________ getChessBoardGame

GameManager::ChessBoardGame GameManager::getChessBoardGame() const
{
  return chess_board;
}

//________________________________________________________________________________________________________  changeTurn

void GameManager::changeTurn()
{
    if (getTurn() == USER1)
        setTurn(USER2);
    else
        setTurn(USER1);
}

//________________________________________________________________________________________________________ setTurn

void GameManager::setTurn(Turn turn)
{
  this->turn = turn;
}

//________________________________________________________________________________________________________ getTurn

GameManager::Turn GameManager::getTurn() const
{
  return turn;
}

//________________________________________________________________________________________________________ setGameName

void GameManager::setGameName(GameName game_name)
{
    this->game_name = game_name;
    this->fileManager.set_Game_Name(game_name);
}

//________________________________________________________________________________________________________  getGameName

GameManager::GameName GameManager::getGameName() const
{
  return game_name;
}

//________________________________________________________________________________________________________ convertOrderToString

string GameManager::convertOrderToString(Chessman::Index src, Chessman::Index dest)
{
  shared_ptr<Chessman> temp_chessman = chess_board->getCell(src).getChessPieces();
  if(temp_chessman == nullptr)
    throw invalid_argument("any chessman not exisetd in this cell.");

  string temp = temp_chessman->getID() + " ";
  temp += to_string(src.first) + to_string(src.second);
  temp += to_string(dest.first) + to_string(dest.second);
  temp += " ";

  //check destination
  temp_chessman = chess_board->getCell(dest).getChessPieces();

  //if a piece is in dest
  if(temp_chessman != nullptr)
    temp += temp_chessman->getID();
  else
    temp += "N";

  temp += "^";

  //king rook
  temp_chessman = chess_board->getCell(src).getChessPieces();
  Chessman::ChessType chess_type = temp_chessman->getChessType();
  if (chess_type == Chessman::KING)

  {
      //if king has moved
      if(!dynamic_cast<King*>(temp_chessman.get())->getMoved()) {
          temp += "#";
      } else{
          temp += "@";
      }
  } else if (chess_type == Chessman::ROOK)

  {
      //if rook has moved
      if(!dynamic_cast<Rook*>(temp_chessman.get())->getMoved()) {
          temp += "#";
      } else {
          temp += "@";
      }
  }

  return temp;
}

//________________________________________________________________________________________________________ undo

pair<Chessman::Index, Chessman::Index> GameManager::undo(bool isTemp)
{
    if (movements.empty())
        return make_pair(Chessman::Index(-1, -1), Chessman::Index(-1, -1));

    string temp = movements.top();
    if (!isTemp) {
        this->fileManager.delete_Last_Move();
        qDebug() << "move in undo: " << QString::fromStdString(temp);
    }
    movements.pop();

    Chessman::Index temp_src;
    User::Score temp_score = 0;

    //________________________________ if a king rook happened
    if(temp.substr(0, 3) == "KRO") {
        size_t pos = temp.find(" ");
        Chessman::Index temp_src = {stoi(temp.substr(pos + 1, 1)), stoi(temp.substr(pos + 2, 1))};
        Chessman::Index temp_dest = {stoi(temp.substr(pos + 3, 1)), stoi(temp.substr(pos + 4, 1))};

        this->checkMove(temp_dest, temp_src);
        this->setMove(temp_dest, temp_src, true, isTemp);

        dynamic_cast<King *>(chess_board->getCell(temp_src).getChessPieces().get())->kingNotMoved();

        temp = movements.top();
        movements.pop();
        this->fileManager.delete_Last_Move();
    }
    //________________________________ if a pawn has promoted
    else if (temp.substr(0, 3) == "PRF") {
        qDebug() << "-----------enterd in prf";
        changeTurn();
        size_t pos = temp.find(" ");
        temp_src = {stoi(temp.substr(pos + 1, 1)), stoi(temp.substr(pos + 2, 1))};
        chess_board->hitChessman(temp_src);

        unsigned int temp_turn;
        if (turn == USER1)
            temp_turn = 0;
        else
            temp_turn = 1;

        chess_board->getCell(temp_src).setChessPieces(users[temp_turn]->removePawnsReach());

        temp = movements.top();
        movements.pop();
        this->fileManager.delete_Last_Move();

        changeTurn();
    }

    //________________________________ return moved piece
    size_t pos = temp.find(" ");
    Chessman::Index src = {stoi(temp.substr(pos + 1, 1)), stoi(temp.substr(pos + 2, 1))};
    Chessman::Index dest = {stoi(temp.substr(pos + 3, 1)), stoi(temp.substr(pos + 4, 1))};

    this->checkMove(dest, src);
    this->setMove(dest, src, true, isTemp);

    //_________________________________ undo for king-rook
    if (chess_board->getCell(src).isFull()) {
        Chessman::ChessType chess_type = chess_board->getCell(src).getChessPieces()->getChessType();
        if (chess_type == Chessman::KING) {
            if ('#' == temp[temp.find("^") + 1]) {
                dynamic_cast<King *>(chess_board->getCell(src).getChessPieces().get())
                    ->kingNotMoved();
            }
        } else if (chess_type == Chessman::ROOK) {
            if ('#' == temp[temp.find("^") + 1]) {
                dynamic_cast<Rook *>(chess_board->getCell(src).getChessPieces().get())
                    ->rookNotMoved();
            }
        }
    }

    size_t pos2 = temp.find(" ", pos + 1);
    //________________________________ if has hit a chessmen
    if (temp[pos2 + 1] != 'N') {
        Chessman::Index hitted_index;
        shared_ptr<Chessman> temp_chessman;
        temp_chessman = users[turn]->getChessman(temp.substr(pos2 + 1, temp.find("^") - pos2 - 1),
                                                 false);

        if (temp.substr(0, 3) != "ENP") {
            hitted_index = dest;
        }

        //-------------------------- if hitted by en-passant move
        else {
            if (turn == USER1) {
                hitted_index = make_pair(dest.first - 1, dest.second);
            }

            else if (turn == USER2) {
                hitted_index = make_pair(dest.first + 1, dest.second);
            }
            allowEnpasan(hitted_index);
        }

        chess_board->addChessmanIndex(temp_chessman->getColor(), hitted_index);
        chess_board->getCell(hitted_index)
            .setChessPieces(users[turn]->backChessmanInGame(temp_chessman->getID()));
    }

    this->changeTurn();

    //____________________________ undo for En-Passant
    if (movements.size() != 0 && temp.substr(0, 3) != "ENP") {
        if (movements.top().substr(0, 2) == "AE") {
            string last = movements.top();
            size_t pos = last.find("E");
            allowEnpasan(make_pair(stoi(last.substr(pos + 1, 1)), stoi(last.substr(pos + 2, 1))));
        }
    }

    if (!isTemp) { //undo neg score
        this->users[turn]->incNegativeScore(5);
        try {
            stoi(temp.substr(temp.find("$") + 1, 2));
            temp_score = stoi(temp.substr(temp.find("$") + 1, 2));
        } catch (invalid_argument) { //if one digit
            temp_score = stoi(temp.substr(temp.find("$") + 1, 1));
        }

        //        qDebug() << "undone score: " << temp_score;
        users[turn]->decScore(temp_score);
    }

    return make_pair(dest, src);
}

//________________________________________________________________________________________________________ restartGame

void GameManager::restartGame()
{
    this->fileManager.resetFile();

    string temp_name1 = users[0]->getName();
    string temp_name2 = users[1]->getName();

    delete users[0];
    users[0] = nullptr;
    delete users[1];
    users[1] = nullptr;

    delete chess_board;
    chess_board = nullptr;

    setUser1(temp_name1);
    setUser2(temp_name2);

    this->turn = USER1;
    size_t size = this->movements.size();
    for (size_t i = 0; i < size; i++)
        movements.pop();

    startGame();
}

//________________________________________________________________________________________________________ endGame

void GameManager::endGame()
{
  delete users[0];
  users[0] = nullptr;
  delete users[1];
  users[1] = nullptr;

  delete chess_board;
  chess_board = nullptr;

  this->turn = USER1;
  size_t size = this->movements.size();
  for(size_t i = 0; i < size; i++)
    movements.pop();
}

//________________________________________________________________________________________________________ randomMovements

pair<Chessman::Index, Chessman::Index> GameManager::randomMovements()
{
    //random piece
    vector<shared_ptr<Chessman>> temp_chessmans = users[turn]->getChessmansIn();

    Chessman::ID temp_id = temp_chessmans[randomNum() % temp_chessmans.size()]->getID();
    Chessman::Index temp_src = chess_board->getIndex(temp_id);

    //random movements
    vector<Chessman::Index> temp_can_go = getCellState(temp_src).first;

    while (temp_can_go.size() == 0) {
        temp_id = temp_chessmans[randomNum() % temp_chessmans.size()]->getID();
        temp_src = chess_board->getIndex(temp_id);
        temp_can_go = getCellState(temp_src).first;
    }

    Chessman::Index temp_dest = temp_can_go[randomNum() % temp_can_go.size()];

    try {
        checkMove(temp_src, temp_dest);
        setMove(temp_src, temp_dest);
    } catch (...) {
    }

    return make_pair(temp_src, temp_dest);
}

//________________________________________________________________________________________________________ extraMovements

bool GameManager::extraMovements()
{
  int temp;
  if(turn == USER1)
    temp = 0;
  else
    temp = 1;

  if(users[temp]->getScore() >= 30)
  {
    users[temp]->decScore(30);
    return true;
  }

  return false;
}

//________________________________________________________________________________________________________ isKingChecked

bool GameManager::isKingChecked()
{
    if (turn == USER1)
        return chess_board->isChecked(chess_board->getIndex(users[0]->getKingID()), Chessman::WHITE)
            .first;

    return chess_board->isChecked(chess_board->getIndex(users[1]->getKingID()), Chessman::BLACK)
        .first;
}

//________________________________________________________________________________________________________ limit_cells_for_king_check

void GameManager::limit_cells_for_king_check(Chessman::Index &src,
                                             std::vector<Chessman::Index> &canGo,
                                             std::vector<Chessman::Index> &canHit)
{
    list<Chessman::Index> tempCango(canGo.begin(), canGo.end());
    list<Chessman::Index> tempCanHit(canHit.begin(), canHit.end());

    //searching fo unwanted moves
    for (Chessman::Index &index : canGo) {
        bool moved;
        //a temp move
        try {
            checkMove(src, index);
            moved = true;
            setMove(src, index, false, true);

        }

        catch (KingIsChecked &s) {
            tempCango.remove(index);
            tempCanHit.remove(index);
        }

        catch (exception &s) {
            qDebug() << s.what();
        }

        if (moved) {
            this->changeTurn();
            this->undo(true);
        }
    }

    canGo.clear();
    canHit.clear();
    copy(tempCango.begin(), tempCango.end(), back_inserter(canGo));
    copy(tempCanHit.begin(), tempCanHit.end(), back_inserter(canHit));
}

//________________________________________________________________________________________________________ analayzeGameStatus
//___________________________// game status will be analyzed after each move

GameManager::GameStatus GameManager::analayzeGameStatus()
{
    //search in all user chessmen
    for (shared_ptr<Chessman> &piece : users[turn]->getChessmansIn()) {
        qDebug() << QString::fromStdString(piece->getIcon());

        if (this->getCellState(this->chess_board->getIndex(piece->getID())).first.size() != 0)
            //if at the least one piece still can move
            return isKingChecked() ? GameStatus::CHECKED : GameStatus::NORMAL;
    }
    //if no piece can move
    return isKingChecked() ? GameStatus::CHECKMATE : GameStatus::STALEMATE;
}

//________________________________________________________________________________________________________ promote

void GameManager::promote(Chessman::Index index, Chessman::ChessType chess_type)
{
  Chessman::Icon  temp_icon = "qrc:/Assets/Icons/";
  Chessman::Color temp_color;
  if (turn == USER1) {
      temp_color = Chessman::Color::WHITE;
      temp_icon += "W";
  } else {
      temp_color = Chessman::Color::BLACK;
      temp_icon += "B";
  }

  users[turn]->hitChessman(chess_board->getCell(index).getChessPieces()->getID(), true);
  string temp_name;
  switch(chess_type)
  {
    case Chessman::KNIGHT:
         chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Knight(temp_color, temp_icon + "Knight.png")));
         temp_name = "H";
      break;

    case Chessman::BISHOP:
         chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Bishop(temp_color, temp_icon + "Bishop.png")));
         temp_name = "B";
      break;

    case Chessman::ROOK:
         chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Rook(temp_color, temp_icon + "Rook.png")));
         temp_name = "R";
      break;

    case Chessman::QUEEN:
         chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Queen(temp_color, temp_icon + "Queen.png")));
         temp_name = "Q";
      break;

    default:
        throw invalid_argument("This ChessType not allow.");
  }

  users[turn]->addToChessmansIn(chess_board->getCell(index).getChessPieces());

  movements.push("PRF" + chess_board->getCell(index).getChessPieces()->getID() + " "
                 + to_string(index.first) + to_string(index.second));

  this->fileManager.saveMove("PRF" + chess_board->getCell(index).getChessPieces()->getID() + " "
                             + to_string(index.first) + to_string(index.second));
}

//________________________________________________________________________________________________________ allowEnpasan

void GameManager::allowEnpasan(Enpasan enpasan)
{
    this->enpasan = enpasan;
}

//________________________________________________________________________________________________________ notAllowEnpasan

void GameManager::notAllowEnpasan()
{
  enpasan = make_pair(100, 100);
}

User::Score GameManager::calucateScoreMovePiece(Chessman::Index src, Chessman::Index dest)
{
    User::Score temp = 0;

    //--------------------------------------------------------------------------------  hit enemy chessman

    if (chess_board->getCell(dest).isFull()) {
        Chessman::ChessType chess_type = chess_board->getCell(dest).getChessPieces()->getChessType();
        switch (chess_type) {
        case Chessman::PAWN:
            temp += 3;
          break;

        case Chessman::ROOK:
        case Chessman::BISHOP:
        case Chessman::KNIGHT:
            temp += 8;
          break;

        case Chessman::QUEEN:
            temp += 15;
          break;

        default:
            break;
        }
    }

    //-------------------------------------------------------------------------------- en-passant score
    shared_ptr<Chessman> srcPiece = chess_board->getCell(src).getChessPieces();
    shared_ptr<Chessman> destPiece = nullptr;
    //---------------------- if white pawn
    if (turn == USER1 && dest.first == 2) {
        if (chess_board->getCell(make_pair(dest.first + 1, dest.second)).isFull()) {
            destPiece = chess_board->getCell(make_pair(dest.first + 1, dest.second)).getChessPieces();
            //------ if piece and piece behind is pawn
            if (dynamic_cast<Pawn *>(destPiece.get()) != nullptr
                && dynamic_cast<Pawn *>(srcPiece.get()) != nullptr
                && destPiece->getColor() != srcPiece->getColor())
                temp += 3;
        }
    }
    //---------------------- if black pawn
    else if (dest.first == 5) {
        if (chess_board->getCell(make_pair(dest.first - 1, dest.second)).isFull()) {
            destPiece = chess_board->getCell(make_pair(dest.first - 1, dest.second)).getChessPieces();
            //----- if piece and piece behind is pawn
            if (dynamic_cast<Pawn *>(destPiece.get()) != nullptr
                && dynamic_cast<Pawn *>(srcPiece.get()) != nullptr
                && destPiece->getColor() != srcPiece->getColor())
                temp += 3;
        }
    }

    //-------------------------------------------------------------------------------- move pawn from half of chessboard

    if (chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::PAWN) {
        if ((src.first <= 3 && dest.first >= 4) || (src.first >= 4 && dest.first <= 3)) {
            temp += 3;
        }
    }

    //    -------------------------- a temp move for gettin status
    bool moved = false;
    try {
        checkMove(src, dest);
        moved = true;
        setMove(src, dest, false, true);
    } catch (exception &s) {
        qDebug() << "exception in score ," << s.what();
    }

    if (moved) {
        //-------------------------------------- check and checkmate score
        changeTurn();
        switch (analayzeGameStatus()) {
        case GameStatus::CHECKED:
            temp += 10;
            break;

        case GameStatus::CHECKMATE:
            temp += 50;
            break;

        default:
            break;
        }

        this->undo(true);
    }

    return temp;
}

//----------------------------------------------------------------------------

void GameManager::incScore(User::Score score)
{
    users[turn]->incScore(score);
}

void GameManager::deccScore(User::Score score)
{
    users[turn]->decScore(score);
}

void GameManager::incNegativeScore(User::Score score)
{
    users[turn]->incNegativeScore(score);
}

void GameManager::decNegativeScore(User::Score score)
{
    users[turn]->decNegativeScore(score);
}

FileManager *GameManager::getFileManager()
{
    return &fileManager;
}

//---------------------------------------------------------------------------- load Moves
//-------------------------------// redo all game moves
void GameManager::loadMoves()
{
    if (fileManager.get_Game_Name() == "")
        throw runtime_error("no file loaded");

    for (unsigned i = 0; i < fileManager.get_Moves().size(); i++)
    {
        string move = fileManager.get_Moves()[i];
        size_t pos = move.find(" ");
        Chessman::Index src = {stoi(move.substr(pos + 1, 1)), stoi(move.substr(pos + 2, 1))};
        Chessman::Index dest = {stoi(move.substr(pos + 3, 1)), stoi(move.substr(pos + 4, 1))};
        qDebug() << turn;
        try {
            //------------------------------------- move
            checkMove(src, dest);
            setMove(src, dest);
        } catch (FinalCellForPawn) {
            //------------------------------------- promotion
            setMove(src, dest);
            promotionForFile(fileManager.get_Moves()[++i]);
        }
        changeTurn();
    }
}

//---------------------------------------------------------------------------- promotion For File

void GameManager::promotionForFile(string move)
{
    if (move.substr(0, 3) != "PRF")
        throw runtime_error("a promotion has conflict");

    size_t pos = move.find(" ");
    Chessman::Index index = {stoi(move.substr(pos + 1, 1)), stoi(move.substr(pos + 2, 1))};

    string id = move.substr(3, 1);
    qDebug() << "*** promotion id: " << id.c_str();

    if (id == "Q")
        promote(index, Chessman::QUEEN);

    else if (id == "H")
        promote(index, Chessman::KNIGHT);

    else if (id == "R")
        promote(index, Chessman::ROOK);

    else if (id == "B")
        promote(index, Chessman::BISHOP);
}

//---------------------------------------------------------------------------- get Winner

short unsigned GameManager::getWinner() const
{
    if (users[0]->getScore() > users[1]->getScore())
        return 0;
    else if(users[1]->getScore() > users[0]->getScore())
        return 1;
    else
        return 2;
}

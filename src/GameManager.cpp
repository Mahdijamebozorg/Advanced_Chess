#include "../include/GameManager.hpp"

#include "../include/Bishop.hpp"
#include "../include/Exceptions.hpp"
#include "../include/King.hpp"
#include "../include/Knight.hpp"
#include "../include/Pawn.hpp"
#include "../include/Queen.hpp"
#include "../include/Rook.hpp"
#include "../include/User.hpp"
#include <ctime>
#include <random>
#include <stdexcept>

#include <QDebug>

using namespace std;

GameManager *GameManager::game_manager = nullptr;

//________________________________________________________________________________________________________

GameManager *&GameManager::get(GameName name)
{
    if (game_manager == nullptr)
        game_manager = new GameManager(name);

    return game_manager;
}

//________________________________________________________________________________________________________

GameManager::GameManager(GameName game_name)
{
    setGameName(game_name);
}

//________________________________________________________________________________________________________

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

//________________________________________________________________________________________________________

void GameManager::startGame()
{
  if(users[0] == nullptr || users[1] == nullptr)
    throw runtime_error("All user not seted.");

  setChessBoardGame(ChessBoard::get(users[0], users[1]));
}

//________________________________________________________________________________________________________

pair<vector<Chessman::Index>, vector<Chessman::Index>> GameManager::getCellState(
    Chessman::Index index)
{
  if(chess_board->getCell(index).getChessPieces() == nullptr) // Check in this home has chessman
      throw EmptySquare("In this home any chessman not founded.");

  if(turn == USER1)
  {
    if(chess_board->getCell(index).getChessPieces()->getColor() == Chessman::BLACK)
      throw AccessDenied("User1 can't selected Black Chessman");
  }
  else
  {
    if(chess_board->getCell(index).getChessPieces()->getColor() == Chessman::WHITE)
      throw AccessDenied("User2 can't selected White Chessman");
  }

  auto tempCellState = chess_board->getCanGo(index, true, enpasan);

  qDebug() << "canGo before limitation" << tempCellState.first;
  //_______________________________remvoe dublicated values
  tempCellState.first.erase(unique(tempCellState.first.begin(), tempCellState.first.end()),
                            tempCellState.first.end());
  tempCellState.second.erase(unique(tempCellState.second.begin(), tempCellState.second.end()),
                             tempCellState.second.end());

  //___________________________________________ limit checkable moves

  limit_cells_for_king_check(index, tempCellState.first, tempCellState.second);

  qDebug() << "canGo after limitation" << tempCellState.first;

  return tempCellState;
}

//________________________________________________________________________________________________________

void GameManager::movePiece(Chessman::Index src, Chessman::Index dest, bool in_undo, bool isTemp)
{
    if (src != dest) {
        if (chess_board->getCell(dest).isFull())
            if (chess_board->getCell(dest).getChessPieces()->getChessType() == Chessman::KING)
                throw ImpossibleHitKing("King Could'nt be hited");

        //_____________________________________________________ check en-passnat
        if ((src.first == 1 && dest.first == 3) || (src.first == 6 && dest.first == 4)) {
            if (chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::PAWN) {
                this->allowEnpasan(dest);
                qDebug() << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAllow en-passant";
            }
        } else {
            this->notAllowEnpasan();
        }

        //_____________________________________________________ check king-rook move
        if (chess_board->getCell(src).isFull()) {
            if (chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::KING
                && in_undo == false) {
                if (dest.second - src.second == 2)
                    movePiece(make_pair(dest.first, dest.second + 1),
                              make_pair(dest.first, dest.second - 1),
                              in_undo);
                else if (src.second - dest.second == 2)
                    movePiece(make_pair(dest.first, dest.second - 2),
                              make_pair(dest.first, dest.second + 1),
                              in_undo);
            }
        }

        //_____________________________________________________ save move in string
        if (in_undo == false)
            movements.push(convertOrderToString(src, dest));

        //_____________________________________________________ hitchessman
        pair<Chessman::ID, Chessman::ID> temp = chess_board->moveChessman(src, dest);

        if (temp.first != "") {
            if (turn == USER1) // move chessman from chessmans_in to chessmans_out in user class
                users[1]->hitChessman(temp.first);
            else
                users[0]->hitChessman(temp.first);
        }
        //_______________________________________________________ en-passant move
        if (temp.second != "") {
            string temp_movement = "ENP ";
            if (turn == USER1) // move chessman from chessmans_in to chessmans_out in user class
            {
                temp_movement += static_cast<char>(97 + dest.first + 1);
                users[1]->hitChessman(temp.second);
            } else {
                temp_movement += static_cast<char>(97 + dest.first - 1);
                users[0]->hitChessman(temp.second);
            }

            //_____________________________________________________ save move
            temp_movement += to_string(dest.second) + temp.second;
            movements.push(temp_movement);
        }

        // if chessman that moved is king or rook moved for it chessman inserted true
        //(king must be at the beggining cell)
        shared_ptr<Chessman> temp_chess = chess_board->getCell(dest).getChessPieces();
        if (temp_chess->getChessType() == Chessman::KING)
            dynamic_cast<King *>(temp_chess.get())->kingMoved();
        else if (temp_chess->getChessType() == Chessman::ROOK)
            dynamic_cast<Rook *>(temp_chess.get())->rookMoved();

        //____________________________________________________ king rook move
        if (temp_chess->getChessType() == Chessman::KING && in_undo == true) {
            if (dest.second - src.second == 2) {
                this->undo();
                dynamic_cast<King *>(temp_chess.get())->kingNotMoved();
                dynamic_cast<Rook *>(
                    chess_board->getCell(make_pair(src.first, src.second - 2)).getChessPieces().get())
                    ->rookNotMoved();
                changeTurn();
            } else if (src.second - dest.second == 2) {
                this->undo();
                dynamic_cast<King *>(temp_chess.get())->kingNotMoved();
                dynamic_cast<Rook *>(
                    chess_board->getCell(make_pair(src.first, src.second + 1)).getChessPieces().get())
                    ->rookNotMoved();
                changeTurn();
            }
        }
        //_____________________________________________________ Promotion
        if (dest.first == 0 || dest.first == 7)
            if (chess_board->getCell(dest).getChessPieces()->getChessType()
                == Chessman::ChessType::PAWN)
                throw FinalCellForPawn("Pawn moved to final cell");

        //_____________________________________________________ check check
        if (isTemp && isKingChecked())
            throw KingIsChecked("_____________king is checked");
    }
}

//________________________________________________________________________________________________________

void GameManager::setUser1(User::Name user1_name, User::Score user1_Pscore, User::Score user1_Nscore)
{
    this->users[0] =  User::get(user1_name, User::Color::WHITE, user1_Pscore, user1_Nscore);
}

//________________________________________________________________________________________________________

void GameManager::setUser2(User::Name user2_name, User::Score user2_Pscore, User::Score user2_Nscore)
{
    this->users[1] = User::get(user2_name, User::Color::BLACK, user2_Pscore, user2_Nscore);
}

//________________________________________________________________________________________________________

GameManager::GameUser GameManager::getUser1() const
{
  return users[0];
}

//________________________________________________________________________________________________________

GameManager::GameUser GameManager::getUser2() const
{
  return users[1];
}

//________________________________________________________________________________________________________

void GameManager::setChessBoardGame(const ChessBoardGame &chess_board)
{
  this->chess_board = chess_board;
}

//________________________________________________________________________________________________________

GameManager::ChessBoardGame GameManager::getChessBoardGame() const
{
  return chess_board;
}

void GameManager::changeTurn()
{
  if(getTurn() == USER1)
    setTurn(USER2);
  else
    setTurn(USER1);
}

//________________________________________________________________________________________________________

void GameManager::setTurn(Turn turn)
{
  this->turn = turn;
}

//________________________________________________________________________________________________________

GameManager::Turn GameManager::getTurn() const
{
  return turn;
}

//________________________________________________________________________________________________________

void GameManager::setGameName(GameName game_name)
{
  this->game_name = game_name;
}

GameManager::GameName GameManager::getGameName() const
{
  return game_name;
}

//________________________________________________________________________________________________________

string GameManager::convertOrderToString(Chessman::Index src, Chessman::Index dest)
{
  shared_ptr<Chessman> temp_chessman = chess_board->getCell(src).getChessPieces();
  if(temp_chessman == nullptr)
    throw invalid_argument("any chessman not exisetd in this cell.");

  string temp = temp_chessman->getID() + " ";
  temp += ((char)(97 + src.first ) + to_string(src.second ));
  temp += ((char)(97 + dest.first) + to_string(dest.second));

  temp_chessman = chess_board->getCell(dest).getChessPieces();
  if(temp_chessman != nullptr)
    temp += temp_chessman->getID();
  else
    temp += "N";

  qDebug() << "qDebug: " << temp.c_str() << endl;
  return temp;
}

//________________________________________________________________________________________________________

pair<Chessman::Index, Chessman::Index> GameManager::undo(bool isTemp)
{
    if (movements.empty())
        return make_pair(Chessman::Index(-1, -1), Chessman::Index(-1, -1));

    string temp = movements.top();
    movements.pop();

    bool temp_enpasan = false;
    Chessman::Index temp_src;
    if (temp.substr(0, 3) == "PRF") // promote
    {
        changeTurn();
        size_t pos = temp.find(" ");
        temp_src = convertIndexStringToIndexInt(temp.substr(pos + 1, 2));
        chess_board->hitChessman(temp_src);

        unsigned int temp_turn;
        if (turn == USER1)
            temp_turn = 0;
        else
            temp_turn = 1;

        chess_board->getCell(temp_src).setChessPieces(users[temp_turn]->removePawnsReach());

        temp = movements.top();
        movements.pop();

        changeTurn();
    } else if (temp.substr(0, 3) == "ENP") // Enpasan
    {
        temp_enpasan = true;
        temp_src = convertIndexStringToIndexInt(temp.substr(4, 2));
        Chessman::ID temp_id = temp.substr(6);

        unsigned int temp_turn;
        if (turn == USER1) {
            temp_turn = 0;
            chess_board->addChessmanIndex(Chessman::WHITE, temp_src);
        } else {
            temp_turn = 1;
            chess_board->addChessmanIndex(Chessman::BLACK, temp_src);
        }

        chess_board->getCell(temp_src).setChessPieces(users[temp_turn]->backChessmanInGame(temp_id));

        temp = movements.top();
        movements.pop();
    }

    size_t pos = temp.find(" ");
    Chessman::Index src = convertIndexStringToIndexInt(temp.substr(pos + 1, 2));
    Chessman::Index dest = convertIndexStringToIndexInt(temp.substr(pos + 3, 2));
    this->movePiece(dest, src, true);

    if (temp.back() != 'N') {
        shared_ptr<Chessman> temp_chessman;
        if (turn == USER2) {
            temp_chessman = users[1]->getChessman(temp.substr(pos + 5), false);
            users[1]->backChessmanInGame(temp.substr(pos + 5));
        } else {
            temp_chessman = users[0]->getChessman(temp.substr(pos + 5), false);
            users[0]->backChessmanInGame(temp.substr(pos + 5));
        }

        this->chess_board->getCell(dest).setChessPieces(temp_chessman);
        chess_board->addChessmanIndex(temp_chessman->getColor(), dest);
    }

    this->changeTurn();

    if (!isTemp) {
        if (turn == USER1)
            this->users[0]->decScore(5);
        else
            this->users[1]->decScore(5);
    }

    if (temp_enpasan)
        allowEnpasan(temp_src);

    return make_pair(src, dest);
}
//________________________________________________________________________________________________________

Chessman::Index GameManager::convertIndexStringToIndexInt(string index) const
{
  int j = 0;
  for(char ch = 'a'; ch <= 'h'; ch++, j++)
  {
    if(ch == index[0])
      return make_pair(j, int(index[1]) - 48);
  }
  throw invalid_argument("string must have 2 charachter and char #0 must between a, h");
}

//________________________________________________________________________________________________________

std::pair<Chessman::Index, Chessman::Index> GameManager::getLastMove()
{
  if(movements.size() == 0)
    throw EmptyMoveMents("move ments is empty");

  if(movements.top().substr(0, 3) == "PRF")
      movements.pop();

  string temp = movements.top();
  int pos = temp.find(" ");
  string src = temp.substr(pos + 1, 2);
  string dest = temp.substr(pos + 3, 2);

  return make_pair(convertIndexStringToIndexInt(src), convertIndexStringToIndexInt(dest));
}

//________________________________________________________________________________________________________

void GameManager::restartGame()
{
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
  for(size_t i = 0; i < size; i++)
    movements.pop();

  startGame();
}

//________________________________________________________________________________________________________

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

//________________________________________________________________________________________________________

pair<bool, pair<Chessman::Index, Chessman::Index>> GameManager::randomMovements()
{
  int temp_turn;
  if(turn == USER1)
    temp_turn = 0;
  else
    temp_turn = 1;

  srand(time(nullptr));

  vector<shared_ptr<Chessman>> temp_chessmans = users[temp_turn]->getChessmansIn();

  Chessman::ID temp_id = temp_chessmans[rand() % temp_chessmans.size()]->getID();

  Chessman::Index temp_src = chess_board->getIndex(temp_id);

  vector<Chessman::Index> temp_can_go = getCellState(temp_src).first;
  if(temp_can_go.size() == 0)
    return make_pair(false, make_pair(make_pair(100, 100), make_pair(100, 100)));

  Chessman::Index temp_dest = temp_can_go[rand() % temp_can_go.size()];

  movePiece(temp_src, temp_dest);

  return make_pair(true, make_pair(temp_src, temp_dest));
}

//________________________________________________________________________________________________________

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

//________________________________________________________________________________________________________

bool GameManager::isKingChecked()
{
    if (turn == USER1)
        return chess_board->isChecked(chess_board->getIndex(users[0]->getKingID()), Chessman::WHITE)
            .first;

    return chess_board->isChecked(chess_board->getIndex(users[1]->getKingID()), Chessman::BLACK)
        .first;
}

//________________________________________________________________________________________________________

void GameManager::limit_cells_for_king_check(Chessman::Index &src,
                                             std::vector<Chessman::Index> &canGo,
                                             std::vector<Chessman::Index> &canHit)
{
    list<Chessman::Index> tempCango(canGo.begin(), canGo.end());
    list<Chessman::Index> tempCanHit(canHit.begin(), canHit.end());

    //searching fo unwanted moves
    for (Chessman::Index &index : canGo) {
        //a temp move
        try {
            movePiece(src, index, false, true);
        }

        catch (KingIsChecked &s) {
            qDebug() << s.what();
            qDebug() << index << " is limited";
            tempCango.remove(index);
            tempCanHit.remove(index);
        }

        catch (exception &s) {
            qDebug() << s.what();
        }

        this->changeTurn();
        this->undo(true);
    }

    canGo.clear();
    canHit.clear();
    copy(tempCango.begin(), tempCango.end(), back_inserter(canGo));
    copy(tempCanHit.begin(), tempCanHit.end(), back_inserter(canHit));
}

//________________________________________________________________________________________________________

GameManager::GameStatus GameManager::analayzeGameStatus()
{
    //search in all user chessmen
    vector<shared_ptr<Chessman>> temp = users[turn]->getChessmansIn();
    for (unsigned i = 0; i < temp.size(); i++) {
        if (this->getCellState(this->chess_board->getIndex(temp[i]->getID())).first.size() != 0) {
            qDebug() << this->getCellState(this->chess_board->getIndex(temp[i]->getID()))
                            .first.size();

            //if at the least one piece still can move
            return isKingChecked() ? GameStatus::CHECKED : GameStatus::NORMAL;
        }
    }
    //if no piece can move
    return isKingChecked() ? GameStatus::CHECKMATE : GameStatus::STALEMATE;
}

//________________________________________________________________________________________________________

short unsigned GameManager::getWinnerIndex() const
{
    return winnerIndex;
}

//________________________________________________________________________________________________________

void GameManager::promote(Chessman::Index index, Chessman::ChessType chess_type)
{
  Chessman::Icon  temp_icon = "qrc:/Assets/Icons/";
  Chessman::Color temp_color;
  unsigned int temp;
  if(turn == USER1)
  {
    temp = 0;
    temp_color = Chessman::Color::WHITE;
    temp_icon += "W";
  }
  else
  {
    temp = 1;
    temp_color = Chessman::Color::BLACK;
    temp_icon += "B";
  }

  users[temp]->hitChessman(chess_board->getCell(index).getChessPieces()->getID(), true);
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

  users[temp]->addToChessmansIn(chess_board->getCell(index).getChessPieces());

  movements.push("PRF" + chess_board->getCell(index).getChessPieces()->getID() + " " +
                 ((char)(97 + index.first)) + to_string(index.second));
}

//________________________________________________________________________________________________________

void GameManager::allowEnpasan(Enpasan enpasan)
{
  this->enpasan = enpasan;
}

//________________________________________________________________________________________________________

void GameManager::notAllowEnpasan()
{
  enpasan = make_pair(100, 100);
}

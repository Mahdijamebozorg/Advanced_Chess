#include "../include/GameManager.hpp"
#include "../include/Bishop.hpp"
#include "../include/Exceptions.hpp"
#include "../include/King.hpp"
#include "../include/Knight.hpp"
#include "../include/Pawn.hpp"
#include "../include/Queen.hpp"
#include "../include/Rook.hpp"
#include "../include/User.hpp"
#include "Utils.cpp"
#include <ctime>
#include <random>

#include <stdexcept>
#include <QDebug>

using namespace std;

GameManager *GameManager::game_manager = nullptr;

//_______________________________________________________________________________________________________ get
// ensure only one obj exists
GameManager *&GameManager::get(GameName name)
{
    if (game_manager == nullptr)
        game_manager = new GameManager(name);

    return game_manager;
}

//_____________________________ __________________________________________________________________________ load game
//-----------------------// sets game data

void GameManager::loadGame(unsigned index)
{
    // load game from file
    fileManager.loadSaveFile(index);

    string name1 = fileManager.get_P1_Name(), name2 = fileManager.get_P2_Name().c_str();

    //------------------------- set users and chessmen
    this->setTurn(Turn::USER1);

    this->game_name = fileManager.get_Game_Name();

    // user 1 setup
    thread user1_th([this, &name1]()
                    {
                        users[0] = User::getInstance(name1, Chessman::Color::WHITE, 0, 0);
                        users[0]->setColor(Chessman::Color::WHITE);
                        users[0]->setChessmansIn(); //
                    });

    // user 2 setup
    thread user2_th([this, &name2]()
                    {
                        users[1] = User::getInstance(name2, Chessman::Color::WHITE, 0, 0);
                        users[1]->setColor(Chessman::Color::BLACK);
                        users[1]->setChessmansIn(); //
                    });

    // ensure users are set before game start
    user1_th.join();
    user2_th.join();

    startGame();

    loadMoves();
}

//________________________________________________________________________________________________________ GameManager

GameManager::GameManager(GameName temp_game_name)
{
    this->game_name = temp_game_name;
}

//________________________________________________________________________________________________________ Distructor

GameManager::~GameManager()
{
    fileManager.resetData();
    resetData();
}

//________________________________________________________________________________________________________ startGame

void GameManager::startGame()
{
    // error if users are no setted
    if (users[0] == nullptr || users[1] == nullptr)
        throw LoadingFailed("All user not setted.");

    setChessBoardGame(ChessBoard::getInstance(users[0], users[1]));
}

//________________________________________________________________________________________________________ getCellState

pair<vector<Chessman::Index>, vector<Chessman::Index>> GameManager::getCellState(
    Chessman::Index index)
{
    // Check if this cell has chessman
    if (chess_board->getCell(index).getChessPieces() == nullptr)
        throw EmptySquare("no chessman in this cell.");

    // if user1 choosed user2 cells
    if (turn == USER1)
    {
        if (chess_board->getCell(index).getChessPieces()->getColor() == Chessman::BLACK)
            throw AccessDenied("User1 can't selected Black Chessman");
    }
    // if user2 choosed user1 cells
    else
    {
        if (chess_board->getCell(index).getChessPieces()->getColor() == Chessman::WHITE)
            throw AccessDenied("User2 can't selected White Chessman");
    }
    auto tempCellState = chess_board->getCanGo(index, true, enpasan);

    // make seprate to calculate in diffrent threads
    auto canGo = &tempCellState.first;
    auto canHit = &tempCellState.second;

    //  _______________________________ remvoe dublicated consecuitive values
    thread th1([&canGo]()
               { canGo->erase(unique(canGo->begin(), canGo->end()),
                              canGo->end()); });
    thread th2([&canHit]()
               { canHit->erase(unique(canHit->begin(), canHit->end()),
                               canHit->end()); });
    th1.join();
    th2.join();

    //  ___________________________________________ limit kimg checkable moves
    //  qDebug() << "-------------- canGo before limitation" << tempCellState.first;

    limit_cells_for_king_check(index, tempCellState.first, tempCellState.second);

    //  qDebug() << "-------------- canGo after limitation" << tempCellState.first;

    return tempCellState;
}

//_______________________________________________________________________________________________ checkMove

void GameManager::checkMove(Chessman::Index src, Chessman::Index dest)
{
    if (src != dest)
    {
        if (!chess_board->getCell(src).isFull())
            throw invalid_argument("no chessman selected (check)");

        //---------------------------------------------------- if wants to hit king
        if (chess_board->getCell(dest).isFull())
            if (chess_board->getCell(dest).getChessPieces()->getChessType() == Chessman::KING)
                throw ImpossibleHitKing("King can't be hited");

        //_____________________________________________________ Promotion
        if ((dest.first == 0 || dest.first == 7))
            if (chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::ChessType::PAWN)
                throw FinalCellForPawn("Pawn moved to final cell");
    }
}

//_______________________________________________________________________________________________ setMove

void GameManager::setMove(
    Chessman::Index src, Chessman::Index dest, bool in_undo, bool isTemp, bool isExtraMove)
{
    if (src != dest)
    {
        if (!chess_board->getCell(src).isFull())
            throw invalid_argument("no chessman selected (set)");

        //---------------- calculate score
        User::Score temp_score = 0;

        if (!in_undo && !isTemp)
        {
            if (isExtraMove)
                temp_score -= 30;
            temp_score += calucateScoreMovePiece(src, dest);
            users[turn]->incScore(temp_score);
        }

        string temp_movement;

        //_____________________________________________________ check en-passnat
        // if (!isTemp)
        // {
        bool isPawn = chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::PAWN;
        // black pawn go 2 ahead or undo 1
        if (isPawn && turn == USER2 &&
            ((src.first == 1 && dest.first == 3) || (src.first == 4 && dest.first == 3)))
        {
            allowEnpasan(dest);
        }

        // white pawn go 2 ahead or undo 1
        else if (isPawn && turn == USER1 &&
                 ((src.first == 6 && dest.first == 4) || (src.first == 3 && dest.first == 4)))
        {
            allowEnpasan(dest);
        }

        else
        {
            notAllowEnpasan();
        }
        // }

        //------------------------- set en-passant mode
        if (enpasan.first == 100 || enpasan.second == 100)
            temp_movement += "NE";
        else
            temp_movement += "AE";

        //------------------ movement index
        temp_movement += to_string(dest.first) + to_string(dest.second) + "%";
        temp_movement += convertOrderToString(src, dest);

        //____________________________________________________________________________ king-rook move

        if (chess_board->getCell(src).isFull())
        {
            if (chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::KING && in_undo == false)

            {
                // right king-rook
                if (dest.second - src.second == 2)
                {
                    checkMove(make_pair(dest.first, dest.second + 1),
                              make_pair(dest.first, dest.second - 1));
                    setMove(make_pair(dest.first, dest.second + 1),
                            make_pair(dest.first, dest.second - 1),
                            in_undo);
                    temp_movement = "KRO" + temp_movement + " #";
                }

                // left king-rook
                else if (src.second - dest.second == 2)
                {
                    checkMove(make_pair(dest.first, dest.second - 2),
                              make_pair(dest.first, dest.second + 1));
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
        if (temp.first != "")
        {
            if (turn == USER1) // move chessman from chessmans_in to chessmans_out in user class
                users[1]->hitChessman(temp.first);
            else
                users[0]->hitChessman(temp.first);
        }
        //___________________________________________________________ en-passant move
        if (temp.second != "")
        {
            string temp_movement_ENP = "ENP%" + chess_board->getCell(dest).getChessPieces()->getID() + " ";
            temp_movement_ENP += to_string(src.first) + to_string(src.second);
            if (turn == USER1) // move chessman from chessmans_in to chessmans_out in user class
            {
                temp_movement_ENP += to_string(dest.first);
                users[1]->hitChessman(temp.second);
            }
            else
            {
                temp_movement_ENP += to_string(dest.first);
                users[0]->hitChessman(temp.second);
            }

            //_____________________________________________________ save move
            temp_movement_ENP += to_string(dest.second) + " " + temp.second + "^$" + to_string(temp_score);
            if (!in_undo && (movements.empty() ? true : temp_movement_ENP != movements.top()))
            {
                if (!isTemp)
                {
                    qDebug() << "enp move: " << (temp_movement_ENP).c_str();

                    fileManager.saveMove(temp_movement_ENP);
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

        // if not in undo and last move is not same as current move
        if (!in_undo && (movements.empty() ? true : tempMove != movements.top()))
        {
            // don't save to file for temporaty moves
            if (!isTemp)
            {
                qDebug() << "move: " << tempMove.c_str();
                fileManager.saveMove(tempMove);
            }
            movements.push(tempMove);
        }

        //_____________________________________________________ check check
        if (!in_undo && isTemp && isKingChecked())
            throw KingIsChecked("King is checked");
    }
}

//________________________________________________________________________________________________________ setUser1

void GameManager::setUser1(User::Name user1_name, User::Score user1_Pscore, User::Score user1_Nscore)
{
    this->users[0] = User::getInstance(user1_name, User::Color::WHITE, user1_Pscore, user1_Nscore);
    fileManager.set_P1_Name(users[0]->getName());
}

//________________________________________________________________________________________________________ setUser2

void GameManager::setUser2(User::Name user2_name, User::Score user2_Pscore, User::Score user2_Nscore)
{
    this->users[1] = User::getInstance(user2_name, User::Color::BLACK, user2_Pscore, user2_Nscore);
    fileManager.set_P2_Name(users[1]->getName());
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
    fileManager.set_newFile(game_name);
}

//________________________________________________________________________________________________________  getGameName

GameManager::GameName GameManager::getGameName() const
{
    return game_name;
}

//________________________________________________________________________________________________________ convertOrderToString

string GameManager::convertOrderToString(Chessman::Index src, Chessman::Index dest)
{
    //--------------------------------------- Source
    shared_ptr<Chessman> temp_chessman = chess_board->getCell(src).getChessPieces();

    if (temp_chessman == nullptr)
        throw invalid_argument("GameManager::convertOrderToString: no chessman exisetd in this cell.");

    // temp += ID + ij + ij
    string temp = temp_chessman->getID() + ' ';
    temp += to_string(src.first) + to_string(src.second);
    temp += to_string(dest.first) + to_string(dest.second);
    temp += ' ';

    //--------------------------------------- Destination
    temp_chessman = chess_board->getCell(dest).getChessPieces();
    // if a piece is in dest
    if (temp_chessman != nullptr)
        temp += temp_chessman->getID();
    else
        temp += "N";

    temp += "^";

    //--------------------------------------- King-Rook
    temp_chessman = chess_board->getCell(src).getChessPieces();
    Chessman::ChessType chess_type = temp_chessman->getChessType();
    if (chess_type == Chessman::KING)

    {
        // if king has moved
        if (!dynamic_cast<King *>(temp_chessman.get())->getMoved())
        {
            temp += "#";
        }
        else
        {
            temp += "@";
        }
    }
    else if (chess_type == Chessman::ROOK)

    {
        // if rook has moved
        if (!dynamic_cast<Rook *>(temp_chessman.get())->getMoved())
        {
            temp += "#";
        }
        else
        {
            temp += "@";
        }
    }

    return temp;
}

//________________________________________________________________________________________________________ undo

pair<Chessman::Index, Chessman::Index> GameManager::undo(bool isTemp)
{
    // if have no move
    if (movements.empty())
        return make_pair(Chessman::Index(-1, -1), Chessman::Index(-1, -1));

    string lastMove = movements.top();
    movements.pop();

    // place first space is move string
    size_t pos = lastMove.find(" ");

    static bool extram_move_has_done;

    if (!isTemp)
    {
        fileManager.delete_Last_Move();
    }

    // if after allowing extra move user pressed undo
    if (isThisExtramMove(lastMove) && !isTemp && !extram_move_has_done)
        changeTurn();

    Chessman::Index temp_src = {stoi(lastMove.substr(pos + 1, 1)), stoi(lastMove.substr(pos + 2, 1))};
    User::Score temp_score = 0;

    //________________________________ King-Rook
    // King-Rook has an extra move to undo
    if (lastMove.substr(0, 3) == "KRO")
    {
        // find move dest
        Chessman::Index temp_dest = {stoi(lastMove.substr(pos + 3, 1)), stoi(lastMove.substr(pos + 4, 1))};

        // undo move
        this->checkMove(temp_dest, temp_src);
        this->setMove(temp_dest, temp_src, true, isTemp);

        // undo kingMoved flag
        dynamic_cast<King *>(chess_board->getCell(temp_src).getChessPieces().get())->kingNotMoved();

        // remove move
        lastMove = movements.top();
        movements.pop();
        fileManager.delete_Last_Move();
    }
    //________________________________ Promotion
    else if (lastMove.substr(0, 3) == "PRF")
    {
        // remove new piece
        chess_board->hitChessman(temp_src);

        // add pawn
        chess_board->getCell(temp_src).setChessPieces(users[!turn]->restoreLastPawnsReached());

        // remove promotion from moves
        lastMove = movements.top();
        movements.pop();

        fileManager.delete_Last_Move();
    }

    //________________________________ return moved piece
    pos = lastMove.find(" ");
    Chessman::Index src = {stoi(lastMove.substr(pos + 1, 1)), stoi(lastMove.substr(pos + 2, 1))};
    Chessman::Index dest = {stoi(lastMove.substr(pos + 3, 1)), stoi(lastMove.substr(pos + 4, 1))};

    // must not cause any error
    this->checkMove(dest, src);
    this->setMove(dest, src, true, isTemp);

    //_________________________________ undo king-rook flags
    // ensure move is done
    if (chess_board->getCell(src).isFull())
    {
        Chessman::ChessType chess_type = chess_board->getCell(src).getChessPieces()->getChessType();
        // if is King
        if (chess_type == Chessman::KING)
        {
            if ('#' == lastMove[lastMove.find("^") + 1])
            {
                dynamic_cast<King *>(chess_board->getCell(src).getChessPieces().get())
                    ->kingNotMoved();
            }
        }
        // if is Rook
        else if (chess_type == Chessman::ROOK)
        {
            if ('#' == lastMove[lastMove.find("^") + 1])
            {
                dynamic_cast<Rook *>(chess_board->getCell(src).getChessPieces().get())
                    ->rookNotMoved();
            }
        }
    }

    //_______________________________________________________________ if has hit a chessmen
    size_t pos2 = lastMove.find(" ", pos + 1);

    if (lastMove[pos2 + 1] != 'N')
    {
        Chessman::Index hitted_index;
        shared_ptr<Chessman> temp_chessman;
        temp_chessman = users[turn]->getChessman(
            lastMove.substr(pos2 + 1, lastMove.find("^") - pos2 - 1), // hitted piece id
            false);

        // hit piece is in dest EXCEPT enp
        if (lastMove.substr(0, 3) != "ENP")
        {
            hitted_index = dest;
        }

        //-------------------------- if hitted by en-passant move
        else
        {
            if (turn == USER1)
            {
                hitted_index = make_pair(dest.first - 1, dest.second);
            }

            else if (turn == USER2)
            {
                hitted_index = make_pair(dest.first + 1, dest.second);
            }
            allowEnpasan(hitted_index);
        }

        // add to board
        chess_board->addToBoard(temp_chessman->getColor(), hitted_index);

        // return piece and add to cell
        chess_board->getCell(hitted_index)
            .setChessPieces(users[turn]->backChessmanToGame(temp_chessman->getID()));
    }

    // --------------------------------------------------------- reallow en-passant
    if (movements.size() != 0) // && temp.substr(0, 3) != "ENP")
    {
        if (movements.top().substr(0, 2) == "AE")
        {
            string last = movements.top();
            size_t pos = last.find("E");
            allowEnpasan(make_pair(stoi(last.substr(pos + 1, 1)), stoi(last.substr(pos + 2, 1))));
        }
    }

    this->changeTurn();

    // --------------------------------------------------------- score calculous
    if (!isTemp)
    {
        // undo neg score
        this->users[turn]->incNegativeScore(5);
        try
        {
            // 3 digits
            temp_score = stoi(lastMove.substr(lastMove.find("$") + 1, 3));
        }
        catch (invalid_argument)
        {
            try
            {
                // 2 digits
                temp_score = stoi(lastMove.substr(lastMove.find("$") + 1, 2));
            }
            catch (invalid_argument)
            {
                // 1 digits
                temp_score = stoi(lastMove.substr(lastMove.find("$") + 1, 1));
            }
        }

        // qDebug() << "undone score: " << temp_score;
        users[turn]->decScore(temp_score);
    }

    // --------------------------------------------------------- Extra move
    // if user in last move allowed extra move
    if (movements.size() != 0 && !isTemp)
    {
        if (isThisExtramMove(movements.top()))
        {
            changeTurn();
            extram_move_has_done = true;
        }
        else
        {
            extram_move_has_done = false;
        }
    }

    return make_pair(dest, src);
}

//________________________________________________________________________________________________________ restartGame

void GameManager::restartGame()
{
    string temp_name1 = users[0]->getName();
    string temp_name2 = users[1]->getName();

    // reset file data before reseting fileManger data
    fileManager.resetFile();

    // reset FileManager data
    fileManager.resetData();

    // reset game data
    resetData();

    // *important* these can't be paralel
    setUser1(temp_name1);
    setUser2(temp_name2);

    startGame();
}

//________________________________________________________________________________________________________

void GameManager::endGame()
{
    fileManager.removeGameFile();
    fileManager.resetData();
    resetData();
}

//________________________________________________________________________________________________________

void GameManager::resetData()
{
    // reset user 1
    thread reset_user1([this]()
                       {
        delete users[0];
        users[0] = nullptr; });

    // reset user 2
    thread reset_user2([this]()
                       {
        delete users[1];
        users[1] = nullptr; });

    // reset board
    thread reset_board([this]()
                       {
        delete chess_board;
        chess_board = nullptr;
        this->turn = USER1; });

    thread reset_moves([this]()
                       {
        for (size_t i = 0; i < this->movements.size(); i++)
            movements.pop(); });

    reset_user1.join();
    reset_user2.join();
    reset_board.join();
    reset_moves.join();
}

//________________________________________________________________________________________________________

void GameManager::saveAndExit()
{
    // save auto saved data
    fileManager.saveManually();

    // reset fileManager
    fileManager.resetData();

    // reset GameManager data
    resetData();
}

//________________________________________________________________________________________________________ randomMovements

pair<Chessman::Index, Chessman::Index> GameManager::randomMovements()
{
    // user pieces
    vector<shared_ptr<Chessman>> temp_chessmans = users[turn]->getChessmansIn();

    // a random user piece
    Chessman::ID temp_id = temp_chessmans[randomNum() % temp_chessmans.size()]->getID();
    Chessman::Index temp_src = chess_board->getIndex(temp_id);

    // random movements
    vector<Chessman::Index> temp_can_go = getCellState(temp_src).first;

    // if this piece can't move
    while (temp_can_go.size() == 0)
    {
        temp_id = temp_chessmans[randomNum() % temp_chessmans.size()]->getID();
        temp_src = chess_board->getIndex(temp_id);
        temp_can_go = getCellState(temp_src).first;
    }

    Chessman::Index temp_dest = temp_can_go[randomNum() % temp_can_go.size()];

    // move
    try
    {
        checkMove(temp_src, temp_dest);
        setMove(temp_src, temp_dest);
        qDebug() << "random move: " << temp_src << temp_dest;
    }
    catch (exception &e)
    {
        qDebug() << e.what();
    }

    return make_pair(temp_src, temp_dest);
}

//________________________________________________________________________________________________________ extraMovements

bool GameManager::extraMovements()
{
    if (users[turn]->getScore() >= 30)
    {
        return true;
    }
    return false;
}
//________________________________________________________________________________________________________

bool GameManager::isThisExtramMove(std::string move)
{
    int temp_score;
    try
    {
        // if score is 3 digits
        temp_score = stoi(move.substr(move.find("$") + 1, 3));
    }
    catch (invalid_argument)
    {
        try
        {
            // " 2 digits
            temp_score = stoi(move.substr(move.find("$") + 1, 2));
        }
        catch (invalid_argument)
        {
            try
            {
                // " 1 digit
                temp_score = stoi(move.substr(move.find("$") + 1, 1));
            }
            catch (invalid_argument)
            {
                return false;
            }
        }
    }
    return temp_score < 0;
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
    // conver to list
    list<Chessman::Index> tempCango(canGo.begin(), canGo.end());
    list<Chessman::Index> tempCanHit(canHit.begin(), canHit.end());

    // searching fo unwanted moves
    for (Chessman::Index &index : canGo)
    {
        bool moved;
        // a temp move
        try
        {
            try
            {
                checkMove(src, index);
            }
            catch (FinalCellForPawn)
            {
            }

            moved = true;
            setMove(src, index, false, true);
        }

        // if move make user ckeck
        catch (KingIsChecked &s)
        {
            tempCango.remove(index);
            tempCanHit.remove(index);
        }

        catch (exception &s)
        {
            qDebug() << s.what();
        }

        // undo
        if (moved)
        {
            this->changeTurn();
            this->undo(true);
        }
    }

    // change canGo and canHit
    canGo.clear();
    canHit.clear();
    copy(tempCango.begin(), tempCango.end(), back_inserter(canGo));
    copy(tempCanHit.begin(), tempCanHit.end(), back_inserter(canHit));
}

//________________________________________________________________________________________________________ analayzeGameStatus
//___________________________// game status will be analyzed after each move

GameManager::GameStatus GameManager::analayzeGameStatus()
{
    bool found = false;

    // search in current user pieces in
    for (shared_ptr<Chessman> &piece : users[turn]->getChessmansIn())
    {
        //        qDebug() << "Checking piece: " << QString::fromStdString(piece->getID()) << this->chess_board->getIndex(piece->getID()) << Qt::endl;

        // this function checks if piece can move, make found true
        auto lf = [this, &found, &piece]()
        {
            if (this->getCellState(this->chess_board->getIndex(piece->getID())).first.size() != 0)
                if (!found)
                    found = true;
        };
        // set a check thread for each piece
        // (wanted to use mutltithreading but error did't let! so each thread must be finished first)
        thread th(lf);
        th.join();

        // if found in this thread
        if (found)
            break;
    }

    // if at the least one piece still can move
    if (found)
        return isKingChecked() ? GameStatus::CHECKED : GameStatus::NORMAL;
    // if no piece can move
    else
        return isKingChecked() ? GameStatus::CHECKMATE : GameStatus::STALEMATE;
}

//________________________________________________________________________________________________________ promote

void GameManager::promote(Chessman::Index index, Chessman::ChessType chess_type)
{
    // set piece icon
    Chessman::Icon temp_icon = "qrc:/Assets/Icons/";

    // set piece color
    Chessman::Color temp_color;
    if (turn == USER1)
    {
        temp_color = Chessman::Color::WHITE;
        temp_icon += "W";
    }
    else
    {
        temp_color = Chessman::Color::BLACK;
        temp_icon += "B";
    }

    // remove current piece
    users[turn]->hitChessman(chess_board->getCell(index).getChessPieces()->getID(), true);

    // add new piece
    switch (chess_type)
    {
    case Chessman::KNIGHT:
        chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Knight(temp_color, temp_icon + "Knight.png")));
        break;

    case Chessman::BISHOP:
        chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Bishop(temp_color, temp_icon + "Bishop.png")));
        break;

    case Chessman::ROOK:
        chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Rook(temp_color, temp_icon + "Rook.png")));
        break;

    case Chessman::QUEEN:
        chess_board->getCell(index).setChessPieces(shared_ptr<Chessman>(new Queen(temp_color, temp_icon + "Queen.png")));
        break;

    default:
        throw invalid_argument("This ChessType is not allowed.");
    }

    // add new piece to user piece
    users[turn]->addToChessmansIn(chess_board->getCell(index).getChessPieces());

    // PRF + ID + IJ
    string promotionMove = "PRF" + chess_board->getCell(index).getChessPieces()->getID() + " " + to_string(index.first) + to_string(index.second);

    // add promote move
    movements.push(promotionMove);

    // save promote move
    fileManager.saveMove(promotionMove);
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

    auto hitL = [this, &temp, &dest]()
    {
        if (chess_board->getCell(dest).isFull())
        {
            Chessman::ChessType chess_type = chess_board->getCell(dest).getChessPieces()->getChessType();
            switch (chess_type)
            {
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
    };

    thread hitCheck(hitL);

    //-------------------------------------------------------------------------------- en-passant score

    auto enpL = [this, &src, &dest, &temp]()
    {
        shared_ptr<Chessman> srcPiece = chess_board->getCell(src).getChessPieces();
        shared_ptr<Chessman> destPiece = nullptr;
        //---------------------- if white pawn
        if (turn == USER1 && dest.first == 2)
        {
            if (chess_board->getCell(make_pair(dest.first + 1, dest.second)).isFull())
            {
                destPiece = chess_board->getCell(make_pair(dest.first + 1, dest.second)).getChessPieces();
                //------ if piece and piece behind is pawn
                if (dynamic_cast<Pawn *>(destPiece.get()) != nullptr && dynamic_cast<Pawn *>(srcPiece.get()) != nullptr && destPiece->getColor() != srcPiece->getColor())
                    temp += 3;
            }
        }
        //---------------------- if black pawn
        else if (dest.first == 5)
        {
            if (chess_board->getCell(make_pair(dest.first - 1, dest.second)).isFull())
            {
                destPiece = chess_board->getCell(make_pair(dest.first - 1, dest.second)).getChessPieces();
                //----- if piece and piece behind is pawn
                if (dynamic_cast<Pawn *>(destPiece.get()) != nullptr && dynamic_cast<Pawn *>(srcPiece.get()) != nullptr && destPiece->getColor() != srcPiece->getColor())
                    temp += 3;
            }
        }
    };

    thread enpCheck(enpL);

    //-------------------------------------------------------------------------------- move pawn from half of chessboard

    auto pHalfL = [this, &temp, &src, &dest]()
    {
        if (chess_board->getCell(src).getChessPieces()->getChessType() == Chessman::PAWN)
        {
            if ((src.first <= 3 && dest.first >= 4) || (src.first >= 4 && dest.first <= 3))
            {
                temp += 3;
            }
        }
    };

    thread pHalfCheck(pHalfL);

    // threads must be done before moving any piece
    hitCheck.join();
    enpCheck.join();
    pHalfCheck.join();

    //    -------------------------- a temp move for getin status
    bool moved = false;
    try
    {
        checkMove(src, dest);
        moved = true;
        setMove(src, dest, false, true);
    }
    catch (exception &s)
    {
    }

    if (moved)
    {
        //-------------------------------------- check and checkmate score
        changeTurn();
        switch (analayzeGameStatus())
        {
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

//----------------------------------------------------------------------------

void GameManager::deccScore(User::Score score)
{
    users[turn]->decScore(score);
}

//----------------------------------------------------------------------------

void GameManager::incNegativeScore(User::Score score)
{
    users[turn]->incNegativeScore(score);
}

//----------------------------------------------------------------------------

void GameManager::decNegativeScore(User::Score score)
{
    users[turn]->decNegativeScore(score);
}

//----------------------------------------------------------------------------

void GameManager::removeSaveFile(unsigned index)
{
    fileManager.removeSaveFile(index);

    // refresh the list
    fileManager.readSaveFiles();
}

//----------------------------------------------------------------------------

void GameManager::readSaveFiles()
{
    fileManager.readSaveFiles();
}

//----------------------------------------------------------------------------

string GameManager::getSaveFileInfo(unsigned index)
{
    return fileManager.getSaveFileInfo(index);
}

//----------------------------------------------------------------------------

std::vector<std::string> GameManager::getSaveFiles()
{
    return fileManager.getSaveFiles();
}

//---------------------------------------------------------------------------- load Moves
//-------------------------------// redo all game moves
void GameManager::loadMoves()
{
    if (fileManager.get_Game_Name() == "")
        throw LoadingFailed("no file loaded");

    // clear file
    fileManager.resetFile();

    for (unsigned i = 0; i < fileManager.get_Moves().size(); i++)
    {
        string move = fileManager.get_Moves()[i];
        qDebug() << "performing loaded move: " << QString::fromStdString(move);
        size_t pos = move.find(" ");
        Chessman::Index src = {stoi(move.substr(pos + 1, 1)), stoi(move.substr(pos + 2, 1))};
        Chessman::Index dest = {stoi(move.substr(pos + 3, 1)), stoi(move.substr(pos + 4, 1))};

        // to emulate choosing piece
        try
        {
            this->getCellState(src);
        }
        catch (...)
        {
        }

        try
        {
            //------------------------------------- move
            checkMove(src, dest);
            setMove(src, dest);
        }
        catch (FinalCellForPawn)
        {
            //------------------------------------- promotion
            if (fileManager.get_Moves().size() > i + 1)
            {
                setMove(src, dest);
                promotionForFile(fileManager.get_Moves()[++i]);
            }
            else
                changeTurn();
        }
        changeTurn();
    }
}

//---------------------------------------------------------------------------- promotion For File
// read states and call promotion while reading save file

void GameManager::promotionForFile(string move)
{
    if (move.substr(0, 3) != "PRF")
    {
        throw runtime_error(move + "promotion data is not complete");
    }

    size_t pos = move.find(" ");
    Chessman::Index index = {stoi(move.substr(pos + 1, 1)), stoi(move.substr(pos + 2, 1))};

    string id = move.substr(3, 1);

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
    else if (users[1]->getScore() > users[0]->getScore())
        return 1;
    else
        return 2;
}

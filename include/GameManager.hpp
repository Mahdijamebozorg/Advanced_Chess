#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "User.hpp"

#include "ChessBoard.hpp"
#include "Filemanager.hpp"

#include <stack>
#include <thread>

class GameManager
{
public:
    using ChessBoardGame = ChessBoard *;
    using GameUser = User *;
    using GameName = std::string;
    using Movements = std::stack<std::string>;
    using Enpasan = Chessman::Index;

    enum Turn
    {
        USER1,
        USER2
    };
    enum GameStatus
    {
        NORMAL,
        CHECKED,
        STALEMATE,
        CHECKMATE
    };

    // Static Singleton Pattern
    static GameManager *&get(GameName name);

    //------------------------------------------------------------------------------------- game setup
    void startGame();
    void restartGame();
    void endGame();

    //-------------------------------------------- File
    FileManager *getFileManager();
    void loadGame(std::string gameName);
    void loadMoves();
    void promotionForFile(std::string move);
    void saveAutoSaved();

    //-------------------------------------------- Board
    void setChessBoardGame(const ChessBoardGame &);
    ChessBoardGame getChessBoardGame() const;

    //--------------------------------------------
    void setUser1(User::Name, User::Score = 0, User::Score = 0);
    GameUser getUser1() const;

    //--------------------------------------------
    void setUser2(User::Name, User::Score = 0, User::Score = 0);
    GameUser getUser2() const;

    //--------------------------------------------
    void setGameName(GameName);
    GameName getGameName() const;

    //--------------------------------------------
    void setTurn(Turn);
    Turn getTurn() const;
    void changeTurn();

    //--------------------------------------------
    ~GameManager();

    //------------------------------------------------------------------------------------- Movements

    // Returns cell canGo and canHit
    std::pair<std::vector<Chessman::Index>, std::vector<Chessman::Index>> getCellState(
        Chessman::Index);

    //-------------------------------------------- Move and hit chessman
    void checkMove(Chessman::Index src,
                   Chessman::Index dest);

    void setMove(Chessman::Index src,       // move source
                 Chessman::Index dest,      // move dest
                 bool in_undo = false,      // if is calling in undo
                 bool isTemp = false,       // if move is not permament
                 bool isExtraMove = false); // is using extra move

    //-------------------------------------------- To save the movement
    // string order: "Chessman(ID) Xi Xi Chessman(ID) or N"
    std::string convertOrderToString(Chessman::Index src, Chessman::Index dest);

    //-------------------------------------------- Undo movement
    std::pair<Chessman::Index, Chessman::Index> undo(bool isTemp = false);

    //--------------------------------------------
    std::pair<Chessman::Index, Chessman::Index> randomMovements();

    //--------------------------------------------
    bool extraMovements();
    bool isThisExtramMove(std::string move);

    //--------------------------------------------
    void limit_cells_for_king_check(Chessman::Index &src,
                                    std::vector<Chessman::Index> &canGo,
                                    std::vector<Chessman::Index> &canHit);

    //-------------------------------------------- When Pawn reach to final cell
    void promote(Chessman::Index, Chessman::ChessType);

    //-------------------------------------------- Enpasan functions
    void allowEnpasan(Enpasan);
    void notAllowEnpasan();

    //    Chessman::Icon getHitPiece();

    //------------------------------------------------------------------------------------- Game States
    // checked kish user
    bool isKingChecked();
    GameStatus analayzeGameStatus();
    short unsigned getWinner() const;

    //------------------------------------------------------------------------------------- Scores
    User::Score calucateScoreMovePiece(Chessman::Index src, Chessman::Index dest);
    void incScore(User::Score);
    void deccScore(User::Score);
    void incNegativeScore(User::Score);
    void decNegativeScore(User::Score);

private:
    // Singeleton Pattern setups
    GameManager(GameName);
    GameManager(const GameManager &) = delete; // Copy constructor
    static GameManager *game_manager;

    std::array<GameUser, 2> users = {nullptr, nullptr};
    ChessBoardGame chess_board = nullptr;
    Turn turn = USER1;
    GameName game_name;
    Movements movements = {};
    Enpasan enpasan = std::make_pair(100, 100);
    FileManager fileManager;
};

#endif /* end of include guard: GAMEMANAGER_H*/

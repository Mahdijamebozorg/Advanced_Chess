#ifndef GAMEMANAGER_HGameManager
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
    static GameManager *&get();

    //------------------------------------------------------------------------------------- Game Setup

    // sets board , users must be set before this
    void startGame();

    // resets data except users and game name
    void restartGame();

    // reset class data
    void resetData();

    // resets and delete save file
    void endGame();

    //-------------------------------------------- File

    // keeps file operation thread
    std::thread fileOperation;

    FileManager *getFileManager(bool endPreviewsOp = true);

    // gets a callable and replace it to fileOp thread
    template <typename Func>
    void addFileOperation(Func);

    // loads game from save files in folder
    void loadGame(unsigned index);

    // performs loaded file moves
    void loadMoves();

    // promotion when reading moves from file
    void promotionForFile(std::string move);

    // renames auto save to normal formm
    void saveAndExit();

    // retun selected save game info
    std::string getSaveFileInfo(unsigned index);

    // returns all save files in this folder
    std::vector<std::string> getSaveFiles();

    // remove selected save file and refreshed the list
    void removeSaveFile(unsigned index);

    // reads all save files in this dir
    void readSaveFiles();

    //-------------------------------------------- Board
    void setChessBoardGame(const ChessBoardGame &);
    ChessBoardGame getChessBoardGame() const;

    //--------------------------------------------
    // adds user 1 name to file, and sets its pieces
    void setUser1(User::Name, User::Score = 0, User::Score = 0);
    GameUser getUser1() const;

    //--------------------------------------------
    // adds user 2 name to file, and sets its pieces
    void setUser2(User::Name, User::Score = 0, User::Score = 0);
    GameUser getUser2() const;

    //--------------------------------------------
    // makes a new file for game save
    void newGame(GameName);
    GameName getGameName() const;

    //--------------------------------------------
    void setTurn(Turn);
    Turn getTurn() const;
    void changeTurn();

    //--------------------------------------------
    GameManager();
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

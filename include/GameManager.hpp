#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "User.hpp"

#include "ChessBoard.hpp"
#include "Filemanager.hpp"

#include <stack>

class GameManager
{
public:
    using ChessBoardGame = ChessBoard *;
    using GameUser = User *;
    using GameName = std::string;
    using Movements = std::stack<std::string>;
    using Enpasan = Chessman::Index;

    enum Turn { USER1, USER2 };
    enum GameStatus { NORMAL, CHECKED, STALEMATE, CHECKMATE };

    // Static Singleton Pattern
    static GameManager *&get(GameName name);

    //------------------------------------------------------------------------------------- game setup
    void startGame();
    void restartGame();
    void endGame();

    //-------------------------------------------- files
    FileManager *getFileManager();
    void loadGame(std::string gameName);
    void loadMoves();
    void promotionForFile(std::string move);
    void saveAutoSaved(); //manually

    void setChessBoardGame(const ChessBoardGame &);
    ChessBoardGame getChessBoardGame() const;

    void setUser1(User::Name, User::Score = 0, User::Score = 0);
    GameUser getUser1() const;

    void setUser2(User::Name, User::Score = 0, User::Score = 0);
    GameUser getUser2() const;

    void setGameName(GameName);
    GameName getGameName() const;

    void setTurn(Turn);
    Turn getTurn() const;
    void changeTurn();

    // Enpasan functions
    void allowEnpasan(Enpasan);
    void notAllowEnpasan();
    // Destructor
    ~GameManager();

    //------------------------------------------------------------------------------------- Movements
    // CanGo functions
    std::pair<std::vector<Chessman::Index>, std::vector<Chessman::Index>> getCellState(
        Chessman::Index);

    // Move and hit chessman
    void checkMove(Chessman::Index src,
                   Chessman::Index dest); //if is testing

    void setMove(Chessman::Index src,
                 Chessman::Index dest,
                 bool in_undo = false,
                 bool isTemp = false);

    // Convert order to string   // string order: "Chessman(ID) Xi Xi Chessman(ID) or N"
    std::string convertOrderToString(Chessman::Index src, Chessman::Index dest);

    // Undo
    std::pair<Chessman::Index, Chessman::Index> undo(bool isTemp = false);

    // Random and Extra Movement functions
    std::pair<Chessman::Index, Chessman::Index> randomMovements();
    bool extraMovements();
    //
    void limit_cells_for_king_check(Chessman::Index &src,
                                    std::vector<Chessman::Index> &canGo,
                                    std::vector<Chessman::Index> &canHit);
    // When Pawn reach to final cell
    void promote(Chessman::Index, Chessman::ChessType);

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

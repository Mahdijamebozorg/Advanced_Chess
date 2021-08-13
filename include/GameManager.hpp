#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "User.hpp"
#include "ChessBoard.hpp"

#include <stack>


class GameManager
{
public:
  // Type alias
  using ChessBoardGame = ChessBoard*            ;
  using GameUser       = User*                  ;
  using GameName       = std::string            ;
  using Movements      = std::stack<std::string>;
  using Enpasan        = Chessman::Index        ;

  // declare enum
  enum Turn {USER1, USER2};
  enum GameStatus { NORMAL, CHECKED, STALEMATE, CHECKMATE };

  // static set and get pointer to this calss functions for Singeleto Pattern
  static GameManager*& get(GameName name);

  // set and get functions
  void            setChessBoardGame(const ChessBoardGame&                       )      ;
  ChessBoardGame  getChessBoardGame(                                            ) const;
  void            setUser1         (User::Name, User::Score = 0, User::Score = 0)      ;
  GameUser        getUser1         (                                            ) const;
  void            setUser2         (User::Name, User::Score = 0, User::Score = 0)      ;
  GameUser        getUser2         (                                            ) const;
  void            setTurn          (Turn                                        )      ;
  Turn            getTurn          (                                            ) const;
  void            changeTurn       (                                            )      ;
  void            setGameName      (GameName                                    )      ;
  GameName        getGameName      (                                            ) const;

  // Enpasan functions
  void allowEnpasan(Enpasan);
  void notAllowEnpasan();

  // CanGo functions
  std::pair<std::vector<Chessman::Index>, std::vector<Chessman::Index>> getCellState(Chessman::Index);

  // Move and hit chessman
  void movePiece(Chessman::Index src,
                 Chessman::Index dest,
                 bool move = false,    // if(move) order move to movements
                 bool isTemp = false); //if is testing

  // Convert order to string   // string order: "Chessman(ID) Xi Xi Chessman(ID) or N"
  std::string convertOrderToString(Chessman::Index src, Chessman::Index dest);

  // convert Index string to index int
  Chessman::Index                             convertIndexStringToIndexInt(std::string index) const;
  std::pair<Chessman::Index, Chessman::Index> getLastMove(                                  )      ;

  // Undo
  std::pair<Chessman::Index, Chessman::Index> undo(bool isTemp = false);

  // Start, End and Restart Game Functions
  void startGame();
  void restartGame();
  void endGame();

  // Random and Extra Movement functions
  std::pair<bool, std::pair<Chessman::Index, Chessman::Index>> randomMovements();
  bool extraMovements();

  // checked kish user
  bool isKingChecked();

  //
  void limit_cells_for_king_check(Chessman::Index &src,
                                  std::vector<Chessman::Index> &canGo,
                                  std::vector<Chessman::Index> &canHit);
  //
  GameStatus analayzeGameStatus();

  short unsigned getWinnerIndex() const;

  // Destructor
  ~GameManager();

  // When Pawn reach to final cell
  void promote(Chessman::Index, Chessman::ChessType);

  private:
  // Construcotr is private for Singeleton Pattern
  GameManager(GameName          )         ;
  GameManager(const GameManager&) = delete; // Copy constructor

  // Data member
  static GameManager*     game_manager                            ;
  std::array<GameUser, 2> users         = {nullptr, nullptr}      ;
  ChessBoardGame          chess_board   = nullptr                 ;
  Turn                    turn          = USER1                   ;
  GameName                game_name                               ;
  Movements               movements     = {}                      ;
  Enpasan                 enpasan       = std::make_pair(100, 100);
  short unsigned winnerIndex = 2;
};

#endif /* end of include guard: GAMEMANAGER_H*/

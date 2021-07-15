#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <array>
#include <memory>
#include <list>

#include "Chessman.hpp"
#include "ChessBoard.hpp"

class GameManager
{
public:
  // Type alias
  using WhiteChessman  = std::array<std::shared_ptr<Chessman>, 16>;
  using BlackChessman  = std::array<std::shared_ptr<Chessman>, 16>;
  using ChessBoardGame = std::shared_ptr<ChessBoard              >;

  // static member functions
  static std::shared_ptr<GameManager> &setGameManager();
  static std::shared_ptr<GameManager> &getGameManager();

  // move and hit chesspieces
  std::list<Chessman::Index> getCanGo (Chessman::ID, Chessman::Index            ) const;
  void                       movePiece(Chessman::Index src, Chessman::Index dest)      ;
  void                       hitPiece (Chessman::Index                          )      ;


private:
  // Data member
  WhiteChessman  white_chessman          ;
  BlackChessman  black_chessman          ;
  ChessBoardGame chess_board    = nullptr;
  // static pointer to this class for Singeleton pattern
  static std::shared_ptr<GameManager> game_manager;

  // private member functions
  // Constructor is private for use of pattern singeleton
  GameManager(                     )         ;
  GameManager(const GameManager&   ) = delete; // Copy Constructor
  // initialize chessmans for start game
  void setChessman      (Chessman::Color);
  void setChessBoardGame(               );
};

#endif /* end of include guard: GAMEMANAGER_H*/

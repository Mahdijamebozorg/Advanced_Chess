#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>
#include <vector>
#include <memory>

#include "Cell.hpp"

class ChessBoard // This class used Singeleton pattern
{
  friend class GameManager;
public:
  // Type alias
  using Cells          = std::array<std::array<Cell, 8>, 8>;
  using WhiteChessman  = std::array<std::shared_ptr<Chessman>, 16>;
  using BlackChessman  = std::array<std::shared_ptr<Chessman>, 16>;

  // Static member functinos for Singeleton pattern
  static std::shared_ptr<ChessBoard>& setChessBoard();
  static std::shared_ptr<ChessBoard>& getChessBoard();

  // move functions
  std::list<Chessman::Index> getCanGo    (Chessman::Index, std::list<Chessman::Index>&);
  void                       moveChessman(Chessman::Index src, Chessman::Index dest   );
  Chessman::ID               hitChessman (Chessman::Index                             );

  // get functions
  const Cell&  getCell(Chessman::Index) const;
  const Cells& getCell(               ) const;


private:
  // Private data member
  // pointer to this class
  static std::shared_ptr<ChessBoard> chess_board;
  // cells of chessboard
  Cells cells;


  // Private member functions
  // Constructor is private
  ChessBoard(                 )         ;
  ChessBoard(const ChessBoard&) = delete; // Copy Construcotr
  // Initial ChessBoard when create chess board
  void setCells(const WhiteChessman&, const BlackChessman&);

};

#endif /* end of include guard: CHESSBOARD_H*/

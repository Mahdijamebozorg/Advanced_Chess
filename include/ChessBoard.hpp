#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>
#include <vector>
#include <memory>
#include "User.hpp"
#include "Cell.hpp"

class User;
class ChessBoard // This class used Singeleton pattern
{
public:
  // Type alias
  using Cells  = std::array<std::array<Cell, 8>, 8>;

  // Static member functinos for Singeleton pattern
  static ChessBoard*& get(User*, User*);

  // Destructor
  ~ChessBoard();

  // CanGo functions
  std::pair<std::vector<Chessman::Index>, std::vector<Chessman::Index>> getCanGo(Chessman::Index, bool check_king_rook = true, Chessman::Index enpasan = std::make_pair(100, 100));

  // Move and hit functions
  std::pair<Chessman::ID, Chessman::ID> moveChessman(Chessman::Index src, Chessman::Index dest);
  Chessman::ID                          hitChessman (Chessman::Index                          );

  // get functions
        Cell&     getCell (Chessman::Index)      ;
  const Cells&    getCells(               ) const;
  Chessman::Index getIndex(Chessman::ID   ) const;

  // kish home
  std::pair<bool, Chessman::Index> isChecked    (Chessman::Index, Chessman::Color); // color is enemy chessmans color

  // chessmans Index functions
  void changeIndex        (Chessman::Index src, Chessman::Index dest, bool hit);
  void removeChessmanIndex(Chessman::Index                                    );
  void addChessmanIndex   (Chessman::Color, Chessman::Index                   );

  // set enpasan
  void setEnpasan  (Chessman::Index, Chessman::Index);
  bool checkEnpasan(Chessman::Index, Chessman::Index);


private:
    // Private data member
    // pointer to this class
    static ChessBoard* chess_board;
    // cells of chessboard
    Cells cells;

    // Index cells that chessmans in them
    std::list<Chessman::Index> white_chessmans;
    std::list<Chessman::Index> black_chessmans;

    // Enpasan
    std::pair<Chessman::Index, Chessman::Index> enpasan = std::make_pair
            (std::make_pair(100, 100), std::make_pair(100, 100));

    // Private member functions
    // Constructor is private
    ChessBoard(User*, User*);
    ChessBoard(const ChessBoard &) = delete; // Copy Construcotr
    // Initial ChessBoard when create chess board
    void setCells(User::ChessmansIn white, User::ChessmansIn black);

};

#endif /* end of include guard: CHESSBOARD_H*/

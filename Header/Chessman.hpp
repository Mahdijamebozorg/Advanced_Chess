#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <string>
#include <list>

class Chessman
{
public:
  // Type alias
  using ChessType = enum { PAWN,
                           BISHOP,
                           KNIGHT,
                           ROOK,
                           QUEEN,
                           KING }; // for prevent from many dynamic_cast
  using Color = enum { WHITE,
                       BLACK };
  using ID = std::string;
  using Index = std::pair<size_t, size_t>;

  // Constructor
  Chessman(Color);
  Chessman(const Chessman &); // Copy constructor

  // set and get functions
  ChessType getChessType() const;
  void setColor(Color);
  Color getColor() const;
  virtual void setID() = 0;
  ID getID() const;

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const = 0;

  // Destructor
  virtual ~Chessman();

protected:
  // protected data member
  ChessType chess_type;
  ID id;

private:
  // Data member
  Color color;
};

#endif /* end of include guard: CHESSMAN_H*/

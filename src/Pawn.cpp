#include "Header/Pawn.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t Pawn::cnt = 1;

Pawn::Pawn(Color color):Chessman(color)
{
  this->chess_type = PAWN;
  setID();
}

Pawn::Pawn(const Pawn & pawn):Chessman(pawn)
{
  this->chess_type = PAWN;
  setID();
}

void Pawn::setID()
{
  this->id = "Pawn_"+ to_string(cnt++);
}

list<Pawn::Index> Pawn::getCellsCanGo(Index index) const
{
  checkRange(index);

  Index temp;

  if(getColor() == WHITE)
  {
    if(index.first == 7)
      throw invalid_argument("White pawn can not be in row #7");

    temp.first = index.first + 1;
  }
  else
  {
    if(index.first == 0)
      throw invalid_argument("White pawn can not be in row #0");

    temp.first = index.first - 1;
  }

  list<Index> l;
  for(int i = -1; i <= 1; i++)
  {
    temp.second = index.second + i;
    l.push_back(temp);
  }

  return l;
}

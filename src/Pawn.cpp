#include "../include/Pawn.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);

size_t Pawn::cnt = 1;

Pawn::Pawn(Color color, Icon icon):Chessman(color)
{
  this->chess_type = PAWN;
  setID  (    );
  setIcon(icon);
}

Pawn::Pawn(const Pawn & pawn):Chessman(pawn)
{
  this->chess_type = PAWN;
  setID  (    );
  setIcon(icon);
}

void Pawn::setID()
{
  Chessman::ID temp = "P";

  if(getColor() == WHITE)
    temp += "W";
  else
    temp += "B";

  temp += to_string(cnt++);

  this->id = temp;
}

list<Pawn::Index> Pawn::getCellsCanGo(Index index) const
{
  checkRange(index);

  pair<int, int> temp;
  list<Index> l;

  //first move for white color

  if (getColor() == WHITE) {
      temp.second = index.second;
      temp.first = index.first - 2;
      try {
          checkRange(temp);
          l.push_back(temp);
      } catch (...) {
      }

      temp.first = index.first - 1;
  }

  // first move for black color

  else {
      temp.second = index.second;
      temp.first = index.first + 2;
      try {
          checkRange(temp);
          l.push_back(temp);
      } catch (...) {
      }

      temp.first = index.first + 1;
  }

  //pawn has 3 forward moves
  for(int i = -1; i <= 1; i++)
  {
    temp.second = index.second + i;
    try
    {
       checkRange(temp);
       l.push_back(temp);
    }
    catch (...)
    {}
  }

  return l;
}

void Pawn::setIcon(Icon icon)
{
  this->icon = icon;
}

#include "../include/Rook.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t Rook::cnt = 1;

Rook::Rook(Color color, Icon icon):Chessman(color)
{
  this->chess_type = ROOK;
  setID  (    );
  setIcon(icon);
}

Rook::Rook(const Rook & rook):Chessman(rook)
{
  this->chess_type = ROOK;
  setID  (    );
  setIcon(icon);
}

void Rook::setID()
{
  Chessman::ID temp = "R";

  if(getColor() == WHITE)
    temp += "W";
  else
    temp += "B";

  temp += to_string(cnt++);

  this->id = temp;
}

list<Rook::Index> Rook::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;
  list<Index> l;

  enum {RIGHT = 0, LEFT, UP, DOWN};
  // first right chessman push in list so left so up and so down delimeter
  // delimeter is pair that first and second equal 100
  for(int i = 0; i < 4; i++)
  {
    temp = index;

    bool in_range = true;
    while(in_range)
    {
      if(i == RIGHT)
        temp.second++;

      else if(i == LEFT)
        temp.second--;

      else if(i == UP)
        temp.first--;

      else if(i == DOWN)
        temp.first++;

      try
      {
        checkRange(temp);
      } catch (out_of_range &w) {
          in_range = false;
          temp = Index(100, 100);
      }

      l.push_back(temp);
    }
  }

  return l;
}

void Rook::setIcon(Icon icon)
{
  this->icon = icon;
}

bool Rook::getMoved() const
{
    return moved;
}

void Rook::rookMoved()
{
    this->moved = true;
}

void Rook::rookNotMoved()
{
 moved = false;
}

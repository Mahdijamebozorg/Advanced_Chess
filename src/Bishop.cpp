#include "../include/Bishop.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t Bishop::cnt = 1;

Bishop::Bishop(Color color, Icon icon):Chessman(color)
{
  this->chess_type = BISHOP;
  setID  (    );
  setIcon(icon);
}

Bishop::Bishop(const Bishop & bishop):Chessman(bishop)
{
  this->chess_type = BISHOP;
  setID  (    );
  setIcon(icon);
}

void Bishop::setID()
{
  Chessman::ID temp = "B";

  if(getColor() == WHITE)
    temp += "W";
  else
    temp += "B";

  temp += to_string(cnt++);

  this->id = temp;
}

list<Bishop::Index> Bishop::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;
  list<Index> l;

  enum {UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT};
  // first North-East and so North-West and so South-East so South-West
  // delimeter is pair both is 100
  for(int i = 0; i < 4; i++)
  {
    temp = index;

    bool in_range = true;
    while(in_range)
    { // 0:North-East 1:North-West 2:South-East 3:South-West
      if(i == UP_RIGHT || i == UP_LEFT)
        temp.first--;
      else if(i == DOWN_RIGHT|| i == DOWN_LEFT)
        temp.first++;

      if(i == UP_RIGHT || i == DOWN_RIGHT)
        temp.second++;
      else if(i == UP_LEFT|| i == DOWN_LEFT)
        temp.second--;

      try
      {
        checkRange(temp);
      }
      catch(invalid_argument &w)
      {
        in_range = false;
        temp = Index(100, 100);
      }

      l.push_back(temp);
    }
  }

  return l;
}

void Bishop::setIcon(Icon icon)
{
  this->icon = icon;
}

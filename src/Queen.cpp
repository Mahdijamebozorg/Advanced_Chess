#include "../include/Queen.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);

size_t Queen::cnt = 1;

Queen::Queen(Color color, Icon icon):Chessman(color)
{
  this->chess_type = QUEEN;
  setID  (    );
  setIcon(icon);
}

Queen::Queen(const Queen & queen):Chessman(queen)
{
  this->chess_type = QUEEN;
  setID  (    );
  setIcon(icon);
}

void Queen::setID()
{
  Chessman::ID temp = "Q";

  if(getColor() == WHITE)
    temp += "W";
  else
    temp += "B";

  temp += to_string(cnt++);

  this->id = temp;
}

list<Queen::Index> Queen::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;
  list<Index> l;

  enum {RIGHT = 0, LEFT, UP, DOWN};
  enum {UP_RIGHT = 4, UP_LEFT, DOWN_RIGHT, DOWN_LEFT};
  for(int i = 0; i < 8; i++)
  {
    temp = index;

    bool in_range = true;
    while(in_range)
    {
      if(i < 4) // if not cross move
      {
        // first right chessman push in list so left so up and so down delimeter
        // delimeter is pair that first and second equal 100
        if(i == RIGHT)  // 0:Right 1:Left 2:UP 3:Down
          temp.second++;
        else if(i == LEFT)
          temp.second--;
        else if(i == UP)
          temp.first--;
        else if(i == DOWN)
          temp.first++;
      }
      else // if cross move
      {
        // first North-East and so North-West and so South-East so Douth-West
        // delimeter is pair both is 100
        if(i == UP_RIGHT || i == UP_LEFT) // 4:North-East 5:North-West 6:South-East 7:South-West
          temp.first--;
        else if( i == DOWN_RIGHT || i == DOWN_LEFT)
          temp.first++;

        if(i == UP_RIGHT || i == DOWN_RIGHT)
          temp.second++;
        else if( i == UP_LEFT || i == DOWN_LEFT)
          temp.second--;
      }

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

void Queen::setIcon(Icon icon)
{
  this->icon = icon;
}

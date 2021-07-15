#include "Knight.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t Knight::cnt = 1;

Knight::Knight(Color color):Chessman(color)
{
  this->chess_type = KNIGHT;
  setID();
}

Knight::Knight(const Knight & knight):Chessman(knight)
{
  this->chess_type = KNIGHT;
  setID();
}

void Knight::setID()
{
  this->id = "Knight_"+ to_string(cnt++);
}

list<Knight::Index> Knight::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;
  list<Index> l;

  for(int i = 0; i < 2; i++)
  {
    for(int j = -1; j <= 1; j += 2)
    {
      if(i == 0)
        temp.second = index.second + j;
      else
        temp.first = index.first + j;

      for(int k = -2; k <= 2; k += 4)
      {
        if(i == 0)
          temp.first = index.first + k;
        else
          temp.second = index.second + k;

        try
        {
          checkRange(temp);
          l.push_back(temp);
        }
        catch(invalid_argument &w)
        {}
        }
      }
  }

  return l;
}

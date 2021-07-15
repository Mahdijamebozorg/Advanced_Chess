#include "Header/Rook.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t Rook::cnt = 1;

Rook::Rook(Color color):Chessman(color)
{
  this->chess_type = ROOK;
  setID();
}

Rook::Rook(const Rook & rook):Chessman(rook)
{
  this->chess_type = ROOK;
  setID();
}

void Rook::setID()
{
  this->id = "Rook_"+ to_string(cnt++);
}

list<Rook::Index> Rook::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;
  list<Index> l;

  // first right chessman push in list so left so up and so down delimeter
  // delimeter is pair that first and second equal 100
  for(int i = 0; i < 4; i++)
  {
    temp = index;

    bool in_range = true;
    while(in_range)
    {
      if(i == 0)
        temp.second++;

      else if(i == 1)
        temp.second--;

      else if(i == 2)
        temp.first--;

      else
        temp.first++;

      try
      {
        checkRange(temp);
      }
      catch(invalid_argument& w)
      {
        in_range = false;
        temp = Index(100, 100);
      }

      l.push_back(temp);
    }
  }

  return l;
}

#include "Bishop.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t Bishop::cnt = 1;

Bishop::Bishop(Color color):Chessman(color)
{
  this->chess_type = BISHOP;
  setID();
}

Bishop::Bishop(const Bishop & bishop):Chessman(bishop)
{
  this->chess_type = BISHOP;
  setID();
}

void Bishop::setID()
{
  this->id = "Bishop_"+ to_string(cnt++);
}

list<Bishop::Index> Bishop::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;
  list<Index> l;

  // first northest and so northwest and so southest so southwest
  // delimeter is pair both is 100
  for(int i = 0; i < 4; i++)
  {
    temp = index;

    bool in_range = true;
    while(in_range)
    {
      if(i == 0 || i == 1)
        temp.first--;
      else
        temp.first++;

      if(i == 0 || i == 3)
        temp.second++;
      else
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

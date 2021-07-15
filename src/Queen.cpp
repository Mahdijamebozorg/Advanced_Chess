#include "Header/Queen.hpp"

#include <vector>
#include <stdexcept>

using namespace std;
extern void checkRange(Chessman::Index);


size_t Queen::cnt = 1;

Queen::Queen(Color color):Chessman(color)
{
  this->chess_type = QUEEN;
  setID();
}

Queen::Queen(const Queen & queen):Chessman(queen)
{
  this->chess_type = QUEEN;
  setID();
}

void Queen::setID()
{
  this->id = "Queen_"+ to_string(cnt++);
}

list<Queen::Index> Queen::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;
  list<Index> l;

  for(int i = 0; i < 8; i++)
  {
    temp = index;

    bool in_range = true;
    while(in_range)
    {
      if(i < 4)
      {
        // first right chessman push in list so left so up and so down delimeter
        // delimeter is pair that first and second equal 100
        if(i == 0)
          temp.second++;
        else if(i == 1)
          temp.second--;
        else if(i == 2)
          temp.first--;
        else if(i == 3)
          temp.first++;
      }
      else
      {
        // first northest and so northwest and so southest so southwest
        // delimeter is pair both is 100
        if(i == 4 || i == 5)
          temp.first--;
        else
          temp.first++;

        if(i == 4 || i == 7)
          temp.second++;
        else
          temp.second--;
      }

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

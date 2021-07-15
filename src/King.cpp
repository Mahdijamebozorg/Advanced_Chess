#include "King.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t King::cnt = 1;

King::King(Color color):Chessman(color)
{
  this->chess_type = KING;
  setID();
}

King::King(const King & king):Chessman(king)
{
  this->chess_type = KING;
  setID();
}

void King::setID()
{
  this->id = "King_"+ to_string(cnt++);
}

list<King::Index> King::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  Index temp;

  list<Index> l;
  for(int i = -1; i <= 1; i++)
  {
    temp.first = index.first + i;
    if(temp.first < 0 || temp.first > 7)
      continue;

    for(int j = -1; j <= 1; i++)
    {
      if(i == 0 && j == 0)
        continue;

      temp.second = index.second + i;
      if(temp.second < 0 || temp.second > 7)
        continue;

      l.push_back(temp);
    }
  }

  return l;
}

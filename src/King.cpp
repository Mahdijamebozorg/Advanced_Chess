#include "../Header/King.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


size_t King::cnt = 1;

King::King(Color color, Icon icon):Chessman(color)
{
  this->chess_type = KING;
  setID  (    );
  setIcon(icon);
}

King::King(const King & king):Chessman(king)
{
  this->chess_type = KING;
  setID  (    );
  setIcon(icon);
}

void King::setID()
{
  Chessman::ID temp = "K";

  if(getColor() == WHITE)
    temp += "W";
  else
    temp += "B";

  temp += to_string(cnt++);

  this->id = temp;
}

list<King::Index> King::getCellsCanGo(Index index) const
{
  checkRange(index); // Checked range index

  pair<int, int> temp;

  list<Index> l;

  if(moved == false) // if king not moved still this chessman can tow home moved for movements: KING-ROOK
  {
    l.push_back(make_pair(index.first, index.second + 2));
    l.push_back(make_pair(index.first, index.second - 2));
  }

  for(int i = -1; i <= 1; i++)
  {
    temp.first = index.first + i;
    if(temp.first < 0 || temp.first > 7)
      continue;

    for(int j = -1; j <= 1; j++)
    {
      if(i == 0 && j == 0)
        continue;

      temp.second = index.second + j;
      if(temp.second < 0 || temp.second > 7)
        continue;

      l.push_back(temp);
    }
  }

  return l;
}

void King::setIcon(Icon icon)
{
  this->icon = icon;
}

void King::kingMoved()
{
  this->moved = true;
}

bool King::getMoved() const
{
  return moved;
}


void King::kingNotMoved()
{
 moved = false;
}

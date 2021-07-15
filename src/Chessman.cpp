#include "Header/Chessman.hpp"

#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);


Chessman::Chessman(Color color)
{
  setColor(color);
}

Chessman::Chessman(const Chessman & chessman)
{
  setColor(chessman.getColor());
}

Chessman::~Chessman()
{}

Chessman::ChessType Chessman::getChessType() const
{
  return chess_type;
}

void Chessman::setColor(Color color)
{
  this->color = color;
}

Chessman::Color Chessman::getColor() const
{
  return color;
}

Chessman::ID Chessman::getID() const
{
  return id;
}

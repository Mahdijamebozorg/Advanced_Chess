#include "Header/Cell.hpp"

using namespace std;


Cell::Cell()
{
  setChessPieces(nullptr);
  setColor      (BLACK  );
}

Cell::Cell(Color color, const ChessPieces& chess_pieces)
{
  setChessPieces(chess_pieces);
  setColor      (color);
}

void Cell::setChessPieces(const ChessPieces& chess_pieces)
{
  this->chess_pieces = chess_pieces;
}

Cell::ChessPieces Cell::getChessPieces() const
{
  return chess_pieces;
}

void Cell::moveChessPieces(Cell& cell)
{
  cell.setChessPieces(getChessPieces());

  this->chess_pieces = nullptr;
}

Chessman::ID Cell::hitChessPieces()
{
  Chessman::ID temp = chess_pieces->getID();
  this->chess_pieces.reset();
  this->chess_pieces = nullptr;

  return temp;
}

void Cell::setColor(Color color)
{
  this->color = color;
}

Cell::Color Cell::getColor() const
{
  return color;
}

bool Cell::isFull() const
{
  if(chess_pieces == nullptr)
    return false;

  return true;
}

Cell::operator bool() const
{
  return isFull();
}

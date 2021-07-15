#include "ChessBoard.hpp"

#include <stdexcept>

using namespace std;

extern void checkRange(Chessman::Index);

// Initialize static data member
shared_ptr<ChessBoard> ChessBoard::chess_board = nullptr;

// static member functinos
std::shared_ptr<ChessBoard>& ChessBoard::setChessBoard()
{
  if(chess_board == nullptr)
  {
    chess_board = shared_ptr<ChessBoard>(new ChessBoard());
  }

  return chess_board;
}

shared_ptr<ChessBoard>& ChessBoard::getChessBoard()
{
  if(chess_board == nullptr)
    throw runtime_error("any chessBoard not existed.");

  return chess_board;
}

ChessBoard::ChessBoard()
{}

void ChessBoard::setCells(const WhiteChessman& white_chessman, const BlackChessman& black_chessman)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if((i + 1) * (j + 1) % 2 != 0)
        cells[i][j].setColor(Cell::WHITE);


      if(i == 0)
        cells[i][j].setChessPieces(white_chessman[j]);

      if(i == 1)
        cells[i][j].setChessPieces(white_chessman[j + 8]);

      if(i == 6)
        cells[i][j].setChessPieces(black_chessman[j + 8]);

      if(i == 7)
        cells[i][j].setChessPieces(black_chessman[j]);
    }
  }
}

list<Chessman::Index> ChessBoard::getCanGo(Chessman::Index index, list<Chessman::Index>& list_cells)
{
  Chessman::ChessType chess_type = cells[index.first][index.second].getChessPieces()->getChessType();
  Chessman::Color color = cells[index.first][index.second].getChessPieces()->getColor();


  list<Chessman::Index> temp;
  if(chess_type == Chessman::PAWN || chess_type == Chessman::KNIGHT || chess_type == Chessman::KING)
  {
    for(auto it = list_cells.begin(); it != list_cells.end(); it++)
      if(color != cells[it->first][it->second].getChessPieces()->getColor())
        temp.push_back(*it);
  }

  else
  {
    for(auto it = list_cells.begin(); it != list_cells.end(); it++)
    {
      if(it->first == 100)
        continue;

      if(cells[it->first][it->second].getChessPieces())
      {
        if(cells[it->first][it->second].getChessPieces()->getColor() != color)
          temp.push_back(*it);

        while(true)
        {
          if((it++)->first == 100)
            break;
        }
      }
      else
      {
        temp.push_back(*it);
      }
    }
  }

  return temp;
}

void ChessBoard::moveChessman(Chessman::Index src, Chessman::Index dest)
{
  this->cells[src.first][src.second].moveChessPieces(cells[dest.first][dest.second]);
}

Chessman::ID ChessBoard::hitChessman(Chessman::Index index)
{
  return cells[index.first][index.second].hitChessPieces();
}

const Cell& ChessBoard::getCell(Chessman::Index index) const
{
  return cells[index.first][index.second];
}

const ChessBoard::Cells& ChessBoard::getCell() const
{
  return cells;
}

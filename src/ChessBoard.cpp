#include "../include/ChessBoard.hpp"

#include <stdexcept>
#include "../include/King.hpp"
#include "../include/Rook.hpp"

#include <QDebug>


using namespace std;

extern void checkRange(Chessman::Index);

// Initialize static data member
ChessBoard *ChessBoard::chess_board = nullptr;

ChessBoard*& ChessBoard::get(User* white_user, User* black_user)
{
  if (chess_board == nullptr)
    chess_board = new ChessBoard(white_user, black_user);

  return chess_board;
}

// Constructor
ChessBoard::ChessBoard(User* white_user, User* black_user)
{
  setCells(white_user->getChessmansIn(), black_user->getChessmansIn());
}

ChessBoard::~ChessBoard()
{
  chess_board = nullptr;
  for(auto &row: cells)
  {
    for(auto &item: row)
    {
      if(item.isFull())
      {
        item.setChessPieces(nullptr);
      }
    }
  }
}

// member functinos
void ChessBoard::setCells(User::ChessmansIn white_chessman, User::ChessmansIn black_chessman)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(((i + 1) % 2 == 0 && (j + 1) % 2 != 0) || (((i + 1) % 2 == 0) && ((j + 1) % 2 == 0)))
        cells[i][j].setColor(Cell::BLACK);

      if(i == 0)
      {
        cells[i][j].setChessPieces(black_chessman[j]);
        black_chessmans.push_back(make_pair(i, j));
      }
      else if(i == 1)
      {
        cells[i][j].setChessPieces(black_chessman[j + 8]);
        black_chessmans.push_back(make_pair(i, j));
      }
      else if(i == 6)
      {
        cells[i][j].setChessPieces(white_chessman[j + 8]);
        white_chessmans.push_back(make_pair(i, j));
      }
      else if(i == 7)
      {
        cells[i][j].setChessPieces(white_chessman[j]);
        white_chessmans.push_back(make_pair(i, j));
      }
    }
  }
}

pair<vector<Chessman::Index>, vector<Chessman::Index>> ChessBoard::getCanGo(Chessman::Index index,
                                                                            bool check_king_rook, Chessman::Index enpasan)
{
  checkRange(index); // Check range index

  // Calls functions gerCellsCanGo of Chessman class
  list<Chessman::Index> list_cells = this->getCell(index).getChessPieces()->getCellsCanGo(index);

  // get Chessman that is located on cell that is index
  shared_ptr<Chessman> chess_man = getCell(index).getChessPieces();
  Chessman::ChessType chess_type = chess_man->getChessType();
  Chessman::Color color = chess_man->getColor();

  vector<Chessman::Index> can_go ;
  vector<Chessman::Index> can_hit;

  if(chess_type == Chessman::PAWN)
  {
    if((index.first == 3 && getCell(index).getChessPieces()->getColor() == Chessman::WHITE) ||
      (index.first == 4 && getCell(index).getChessPieces()->getColor() == Chessman::BLACK))
    {
      if(enpasan.first != 100 && enpasan.second != 100)
      {
        if(color == Chessman::WHITE)
        {
          if(list_cells.front().first == enpasan.first - 1 && list_cells.front().second == enpasan.second)
            can_go.push_back(list_cells.front());
          else if((++list_cells.begin())->first == enpasan.first - 1 && (++list_cells.begin())->second == enpasan.second)
            can_go.push_back(*(++list_cells.begin()));
        }
        else
        {
          if(list_cells.front().first == enpasan.first + 1 && list_cells.front().second == enpasan.second)
            can_go.push_back(list_cells.front());
          else if((++list_cells.begin())->first == enpasan.first + 1 && (++list_cells.begin())->second == enpasan.second)
            can_go.push_back(*(++list_cells.begin()));
        }
      }
      if(can_go.size() != 0)
        setEnpasan(index, can_go.front());

    list_cells.pop_front();
    list_cells.pop_front();
    }

    if(!getCell(list_cells.front()).isFull())
    {
      if(index.first == 1 && getCell(index).getChessPieces()->getColor() == Chessman::BLACK)
      {
         if(!getCell(make_pair(list_cells.front().first - 1, list_cells.front().second)).isFull())
           can_go.push_back(list_cells.front());
      }
      else if(index.first == 6 && getCell(index).getChessPieces()->getColor() == Chessman::WHITE)
      {
        if(!getCell(make_pair(list_cells.front().first + 1, list_cells.front().second)).isFull())
          can_go.push_back(list_cells.front());
      }
    }

    if(index.first != 1 && index.first != 6)
      list_cells.pop_front();

    for(auto &item: list_cells)
    {
      if(getCell(item).isFull())
      {
        if(item.second == index.second)
            continue;

        if(getCell(item).getChessPieces()->getColor() == color)
            continue;

        can_go. push_back(item);
        can_hit.push_back(item);
      }
      else
      {
        if(item.second == index.second)
            can_go.push_back(item);
      }
    }
  }
  else if(chess_type == Chessman::KNIGHT || chess_type == Chessman::KING)
  {
    if(chess_type == Chessman::KING)
    {
      Chessman::Color temp_color;
      if(color == Chessman::WHITE)
        temp_color = Chessman::BLACK;
      else
        temp_color = Chessman::WHITE;

      if(dynamic_cast<King*>(chess_man.get())->getMoved() == false)
      {
        if(check_king_rook)
        {
            if(isChecked(index, temp_color).first == false)
            {
              for(int i = 0; i < 2; i++) // i == 0 king move to right, i == 1 king moved to left
              {
                Chessman::Index temp = index;
                for(int k = 0; k <= i + 2; k++)
                {
                  if(i == 0)
                    temp.second++;
                  else
                    temp.second--;

                  if(temp.second == 7 || temp.second == 0)
                  {
                    if(chess_board->getCell(temp).isFull())
                      if(chess_board->getCell(temp).getChessPieces()->getChessType() == Chessman::ROOK)
                        if(dynamic_cast<Rook*>(chess_board->getCell(temp).getChessPieces().get())->getMoved() == false)
                        {
                          if(i == 0)
                            can_go.push_back(list_cells.front()); // right
                          else
                            can_go.push_back(*(++list_cells.begin())); // left
                        }

                    break;
                  }

                    if(chess_board->getCell(temp).isFull())
                       break;

                    if(isChecked(temp, temp_color).first)
                        break;
                  }
                }
            }
        }

        list_cells.pop_front();
        list_cells.pop_front();
      }
    }

    for(auto it = list_cells.begin(); it != list_cells.end(); it++)
    {
      if(cells[it->first][it->second].getChessPieces() == nullptr)
        can_go.push_back(*it);

      else if(color != cells[it->first][it->second].getChessPieces()->getColor())
      {
        can_go. push_back(*it);
        can_hit.push_back(*it);
      }
    }
  }
  else
  {
    for(auto it = list_cells.begin(); it != list_cells.end(); it++)
    {
      if(it->first == 100)
        continue;

      if(getCell(*it).isFull())
      {
        if(getCell(*it).getChessPieces()->getColor() != color)
        {
          can_go. push_back(*it);
          can_hit.push_back(*it);
        }

        while(true)
        {
          if((it)->first == 100)
            break;

          it++;
        }
      }
      else
      {
        can_go.push_back(*it);
      }
    }
  }

  return make_pair(can_go, can_hit);
}

pair<Chessman::ID, Chessman::ID> ChessBoard::moveChessman(Chessman::Index src, Chessman::Index dest)
{
  pair<string, string> temp = make_pair("", "");
  if(getCell(dest).isFull())
  {
    if(getCell(dest).getChessPieces()->getColor() == getCell(src).getChessPieces()->getColor())
      throw invalid_argument("This move cannot be preforemd.");

    temp.first = this->hitChessman(dest);
  }

  this->getCell(src).moveChessPieces(getCell(dest));

  if(checkEnpasan(src, dest))
  {
    if(getCell(dest).getChessPieces()->getColor() == Chessman::WHITE)
    {
      temp.second = this->hitChessman(make_pair(dest.first + 1, dest.second));
      removeChessmanIndex(make_pair(dest.first + 1, dest.second));
    }
    else
    {
      temp.second = this->hitChessman(make_pair(dest.first - 1, dest.second));
      removeChessmanIndex(make_pair(dest.first - 1, dest.second));
    }
  }

  if(temp.first == "")
    changeIndex(src, dest, false);
  else
    changeIndex(src, dest, true );

  return temp;
}

Chessman::ID ChessBoard::hitChessman(Chessman::Index index)
{
  return getCell(index).hitChessPieces();
}

Cell& ChessBoard::getCell(Chessman::Index index)
{
  return cells[index.first][index.second];
}

const ChessBoard::Cells& ChessBoard::getCells() const
{
  return cells;
}

Chessman::Index ChessBoard::getIndex(Chessman::ID id) const
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(cells[i][j].isFull())
      {
        if(cells[i][j].getChessPieces()->getID() == id)
        {
          return make_pair(i, j);
        }
      }
    }
  }

  throw invalid_argument("Any Chessman With this id not founded.");
}

void ChessBoard::changeIndex(Chessman::Index src, Chessman::Index dest, bool hit)
{
  for(auto it = white_chessmans.begin(); it != white_chessmans.end(); it++)
  {
    if(*it == src)
    {
      if(hit)
        this->removeChessmanIndex(dest);

      white_chessmans.erase(it);
      white_chessmans.push_back(dest);

      return;
    }
  }

  for(auto it = black_chessmans.begin(); it != black_chessmans.end(); it++)
  {
    if(*it == src)
    {
      if(hit)
        this->removeChessmanIndex(dest);

      black_chessmans.erase(it);
      black_chessmans.push_back(dest);

      return;
    }
  }

  throw invalid_argument("This Cell is empty.");
}

void ChessBoard::removeChessmanIndex(Chessman::Index index)
{
  for(auto it = white_chessmans.begin(); it != white_chessmans.end(); it++)
  {
    if(*it == index)
    {
      white_chessmans.erase(it);
      return ;
    }
  }

  for(auto it = black_chessmans.begin(); it != black_chessmans.end(); it++)
  {
    if(*it == index)
    {
      black_chessmans.erase(it);
      return ;
    }
  }

  throw invalid_argument("This Cell is empty.");
}

pair<bool, Chessman::Index> ChessBoard::isChecked(
    Chessman::Index userKingIndex, Chessman::Color userColor) // color is enemy chessmans color
{
    //if white Chessmen are checking black king
    if (userColor == Chessman::BLACK) {
        for (auto &item : white_chessmans) {
            auto temp_go = this->getCanGo(item, false).second;
            for (auto &item2 : temp_go) {
                if (item2 == userKingIndex) {
                    qDebug() << "white Chessmen are checking black king";
                    return make_pair(true, userKingIndex);
                }
            }
        }
    }
    //if black Chessmen are checking white king
    else {
        for (auto &item : black_chessmans) {
            auto temp_go = this->getCanGo(item, false).second;
            for (auto &item2 : temp_go) {
                if (item2 == userKingIndex) {
                    qDebug() << "black Chessmen are checking white king";
                    return make_pair(true, userKingIndex);
                }
            }
        }
    }

    return make_pair(false, make_pair(100, 100));
}

void ChessBoard::addChessmanIndex(Chessman::Color color, Chessman::Index index)
{
  if(color == Chessman::WHITE)
    white_chessmans.push_back(index);
  else
    black_chessmans.push_back(index);
}

void ChessBoard::setEnpasan(Chessman::Index src, Chessman::Index dest)
{
  enpasan.first  = src ;
  enpasan.second = dest;
}

bool ChessBoard::checkEnpasan(Chessman::Index src, Chessman::Index dest)
{
  if(this->enpasan.first == src && this->enpasan.second == dest)
    return true;

  return false;
}

vector<Chessman::Index> ChessBoard::getcheckedWay(Chessman::Index src, Chessman::Index dest) // destination must be full
{
  if(getCell(dest).isFull() == false)
    throw invalid_argument("destination is empty");

  shared_ptr<Chessman> chess = getCell(dest).getChessPieces();
  Chessman::Color      color = chess->getColor();

  vector<Chessman::Index> way;
  Chessman::Index temp;
  if(chess->getChessType() == Chessman::PAWN)
  {
    if(color == Chessman::WHITE)
      temp.first = dest.first - 1;
    else
      temp.first = dest.first + 1;

    if(src.second > dest.second)
      temp.second = dest.second + 1;
    else if(dest.second > src.second)
      temp.second = dest.second - 1;
    else
      return way;
    try
    {
      checkRange(temp);
      way.push_back(temp);
    }
    catch(...)
    {
      return way;
    }
  }
  else if(chess->getChessType() == Chessman::KING)
  {
    temp = dest;
    for(int i = -1; i <= 1; i++)
    {
      temp.first += i;
      for(int j = -1; j <= 1; j++)
      {
        temp.second += j;
        try
        {
          checkRange(temp);
          way.push_back(temp);
        }
        catch(...)
        {}
      }
    }

    return way;
  }
  else if(chess->getChessType() == Chessman::KNIGHT)
  {
    auto temp_can_go = chess->getCellsCanGo(dest);
    for(auto item: temp_can_go)
      way.push_back(item);

    return way;
  }
  else if(chess->getChessType() == Chessman::ROOK || chess->getChessType() == Chessman::BISHOP || chess->getChessType() == Chessman::QUEEN)
  {
    return getCanGo(dest).first;
  }
}

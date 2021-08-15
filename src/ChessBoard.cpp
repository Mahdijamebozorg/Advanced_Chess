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

//___________________________________________________________________________________________________ set cells in game start

// member functinos
void ChessBoard::setCells(User::ChessmansIn white_chessman, User::ChessmansIn black_chessman)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
        //setting cell colors
        if (((i + 1) % 2 == 0 && (j + 1) % 2 != 0) || (((i + 1) % 2 == 0) && ((j + 1) % 2 == 0)))
            cells[i][j].setColor(Cell::BLACK);

        if (i == 0) {
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

//______________________________________________________________________________________________________ Can Go

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
      //______________________________________________if this pawn can En-passant

      if ((index.first == 3 && getCell(index).getChessPieces()->getColor() == Chessman::WHITE)
          || (index.first == 4 && getCell(index).getChessPieces()->getColor() == Chessman::BLACK))

      {
          //____________________________________________________ if En-passnat is allowed
          if (enpasan.first != 100 && enpasan.second != 100) {
              if (color == Chessman::WHITE) {
                  if ((list_cells.front().first == enpasan.first - 1) && (list_cells.front().second == enpasan.second)){
                      can_go.push_back(list_cells.front());
                  }
                  else if (((*(++list_cells.begin())).first == enpasan.first - 1) && ((*(++list_cells.begin())).second == enpasan.second)){
                      can_go.push_back(*(++list_cells.begin()));
                  }
              } else {
                  if ((list_cells.front().first == enpasan.first + 1) && (list_cells.front().second == enpasan.second)) {
                      can_go.push_back(list_cells.front());
                  }
                  else if (((*(++list_cells.begin())).first == enpasan.first + 1) && ((*(++list_cells.begin())).second == enpasan.second)) {
                      can_go.push_back(*(++list_cells.begin()));
                  }
              }
          }

          //--------------------- if En-passant is OK
          if (can_go.size() != 0)
          {
              setEnpasan(index, can_go.front());
          }
          list_cells.pop_front();
          list_cells.pop_front();
      }
      //----------------------------- check first move for black pawn
      if (color == Chessman::BLACK) {
          if (index.first != 6) {
              if ((index.first != 1)
                  || (getCell(make_pair(list_cells.front().first - 1, list_cells.front().second))
                          .isFull())
                  || (getCell(list_cells.front()).isFull())) {
                  list_cells.pop_front();
              }
          }
      }

      //----------------------------- check first move for white pawn
      else if (color == Chessman::WHITE) {
          if (index.first != 1) {
              if ((index.first != 6)
                  || (getCell(make_pair(list_cells.front().first + 1, list_cells.front().second))
                          .isFull())
                  || (getCell(list_cells.front()).isFull())) {
                  list_cells.pop_front();
              }
          }
      }

      for (auto &item : list_cells) {
          //-------------------- if there is a piece in canGo list
          if (getCell(item).isFull()) {
              //------- if not cross move
              if (item.second == index.second)
                  continue;

              //---------------------if is ally
              if (getCell(item).getChessPieces()->getColor() == color)
                  continue;

              //-----------------------if is enemy --> cango there
              can_go.push_back(item);
              can_hit.push_back(item);
          }
          //------------------ if can go forward
          else {
              if (item.second == index.second)
                  can_go.push_back(item);
          }
      }
  }

  else if (chess_type == Chessman::KNIGHT || chess_type == Chessman::KING) {
      if (chess_type == Chessman::KING) {
          //if is king first move
          if (dynamic_cast<King *>(chess_man.get())->getMoved() == false) {
              if (check_king_rook)

              {
                  //if king isn't checked
                  if (isChecked(index, color).first == false) {
                      for (int i = 0; i < 2;
                           i++) // i == 0 king move to right, i == 1 king moved to left
                      {
                          Chessman::Index temp = index;
                          for (int k = 0; k <= i + 2; k++) {
                              if (i == 0)
                                  temp.second++;
                              else
                                  temp.second--;

                              if(temp.second != 0 && temp.second != 7) {
                                  //if there is a piece on the way
                                  if(getCell(temp).isFull())
                                      break;

                                  //if this cell is checked
                                  if(isChecked(temp, color).first)
                                      break;
                              } else {
                                  if(!getCell(temp).isFull())
                                      break;

                                  if(!(getCell(temp).getChessPieces()->getChessType() == Chessman::ROOK))
                                     break;

                                  if(dynamic_cast<Rook*>(getCell(temp).getChessPieces().get())->getMoved())
                                    break;

                                  if (i == 0)
                                      can_go.push_back(list_cells.front()); // right
                                  else
                                      can_go.push_back(*(++list_cells.begin())); // left
                              }
                          }
                      }
                  }
              }

              list_cells.pop_front();
              list_cells.pop_front();
          }
      }

      //------------------------------------------------------ king and knight
      for (auto it = list_cells.begin(); it != list_cells.end(); it++)

      {
          //-------------------------------------if no piece in this cell
          if (cells[it->first][it->second].getChessPieces() == nullptr)
              can_go.push_back(*it);

          //-------------------------------------if there is a enemy piece in this cell
          else if (color != cells[it->first][it->second].getChessPieces()->getColor()) {
              can_go.push_back(*it);
              can_hit.push_back(*it);
          }
      }

  }

  //---------------------------------------------------------- for other chessmen
  else {
      for (auto it = list_cells.begin(); it != list_cells.end(); it++)

      {
          //-----------------if out of range
          if (it->first == 100)
              continue;

          //----------------------- if there is a enemy piece in this cell
          if (getCell(*it).isFull()) {
              if (getCell(*it).getChessPieces()->getColor() != color) {
                  can_go.push_back(*it);
                  can_hit.push_back(*it);
              }

              while (true) {
                  //if reaches the limitation
                  if ((it)->first == 100)
                      break;

                  it++;
              }
          } else {
              can_go.push_back(*it);
          }
      }
  }
  return make_pair(can_go, can_hit);
}

//___________________________________________________________________________________________________ move

pair<Chessman::ID, Chessman::ID> ChessBoard::moveChessman(Chessman::Index src, Chessman::Index dest)
{
    pair<string, string> temp = make_pair("", "");

    //-----------------------------if there is piece
    if (getCell(dest).isFull())

    {
        //if is ally
        if (getCell(dest).getChessPieces()->getColor() == getCell(src).getChessPieces()->getColor())
            throw invalid_argument("This move cannot be preforemd.");

        temp.first = this->hitChessman(dest);
    }

    this->getCell(src).moveChessPieces(getCell(dest));

    //------------------------------ allow En-passant move
    if (checkEnpasan(src, dest)) {
        if (getCell(dest).getChessPieces()->getColor() == Chessman::WHITE) {
            temp.second = this->hitChessman(make_pair(dest.first + 1, dest.second));
            removeChessmanIndex(make_pair(dest.first + 1, dest.second));
        } else {
            temp.second = this->hitChessman(make_pair(dest.first - 1, dest.second));
            removeChessmanIndex(make_pair(dest.first - 1, dest.second));
        }
    }

    //------------------------------- change index chessman in saved indexes
    //if doesn't hit any chessmen
    if (temp.first == "")
        changeIndex(src, dest, false);

    //if hit a chessmen
    else
        changeIndex(src, dest, true);

    return temp;
}

//___________________________________________________________________________________________________  hit

Chessman::ID ChessBoard::hitChessman(Chessman::Index index)
{
  return getCell(index).hitChessPieces();
}

//___________________________________________________________________________________________________ getCell

Cell& ChessBoard::getCell(Chessman::Index index)
{
  return cells[index.first][index.second];
}

//___________________________________________________________________________________________________ getCells

const ChessBoard::Cells& ChessBoard::getCells() const
{
  return cells;
}

//___________________________________________________________________________________________________ getIndex
//-----------------------------//searches chessman index by id

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

//___________________________________________________________________________________________________ changeIndex
//-----------------------------//searches in indexes and changes wanted one

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

//___________________________________________________________________________________________________ removeChessmanIndex

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

//___________________________________________________________________________________________________ isChecked
//-----------------------------//check if this id is being checked or not

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

//___________________________________________________________________________________________________ addChessmanIndex

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

//___________________________________________________________________________________________________ checkEnpasan

bool ChessBoard::checkEnpasan(Chessman::Index src, Chessman::Index dest)
{
  if(this->enpasan.first == src && this->enpasan.second == dest)
    return true;

  return false;
}

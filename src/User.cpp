#include "../include/User.hpp"

#include "../include/Bishop.hpp"
#include "../include/ChessBoard.hpp"
#include "../include/King.hpp"
#include "../include/Knight.hpp"
#include "../include/Pawn.hpp"
#include "../include/Queen.hpp"
#include "../include/Rook.hpp"

#include <stdexcept>
#include <QDebug>


using namespace std;

std::array<User *, 2> User::users = {nullptr, nullptr};
int User::cnt = 0;

User*& User::get(Name name, Color color, Score positive_score, Score negative_score)
{
    if (cnt < 2)
        users[cnt++] = new User(name, color, positive_score, negative_score);

    return users[cnt - 1];
}

User::User(Name name, Color color, Score score, Score negative_score)
{
  setName (name );
  setColor(color);
  setScore(score);
  setNegativeScore(negative_score);
  setChessmansIn();
}

void User::setName(Name name)
{
  this->name = name;
}

User::Name User::getName() const
{
  return name;
}

void  User::setColor(Color color)
{
  this->color = color;
}

User::Color User::getColor() const
{
  return color;
}

void User::setScore(Score score)
{
  this->score = score;
}

User::Score User::getScore() const
{
  return score;
}

void User::setNegativeScore(Score score)
{
  this->negative_score = score;
}

User::Score User::getNegativeScore() const
{
  return negative_score;
}

User::Score User::incScore(Score score)
{
  this->score += score;

  return score;
}

User::Score User::decScore(Score score)
{
  return this->score -= score;
}

User::Score User::incNegativeScore(Score score)
{
  return this->negative_score += score;
}

User::Score User::operator+(Score score) const
{
  return this->score + score;
}

User::Score User::operator-(Score score) const
{
  return this->score - score;
}

User::Score User::operator+=(Score score)
{
  return this->score += score;
}

User::Score User::operator-=(Score score)
{
    return this->score -= score;
}

void User::setChessmansIn()
{
  chessmans_in.push_back(shared_ptr<Chessman>(new Rook  (color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Knight(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Bishop(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Queen (color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new King  (color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Bishop(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Knight(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Rook  (color)));

  for(int i = 8; i < 16; i++)
  {
    chessmans_in.push_back(shared_ptr<Chessman>(new Pawn(color)));
  }

  string temp_color;
  if(color == Chessman::WHITE)
    temp_color = "W";
  else
    temp_color = "B";

  string file_addres = "qrc:/Assets/Icons/" + temp_color;
  string names[16] = {"Rook", "Knight", "Bishop", "Queen", "King", "Bishop", "Knight", "Rook"};
  for(int i = 8; i < 16; i++)
    names[i] = "Pawn";

  for(size_t i = 0; i < chessmans_in.size(); i++)
    chessmans_in[i]->setIcon(file_addres + names[i] + ".png");
}

User::ChessmansIn User::getChessmansIn() const
{
  return chessmans_in;
}

User::ChessmansOut User::getChessmansOut() const
{
  return chessmans_out;
}

shared_ptr<Chessman> User::getChessman(Chessman::ID id, bool in) const
{
  if(in)
  {
    for(auto const &item: chessmans_in)
      if(item->getID() == id)
        return item;
  }
  else
  {
    for(auto const &item: chessmans_out)
      if(item->getID() == id)
        return item;
  }

  throw invalid_argument("Any Chessman with this id not existed.");
}

void User::hitChessman(Chessman::ID id, bool chessman_pawn)
{
  for(auto it = chessmans_in.begin(); it != chessmans_in.end(); it++)
  {
    if((*it)->getID() == id)
    {
      if(chessman_pawn)
        pawns_reach_last.push_back(*it);
      else
        chessmans_out.push_back(*it);

      *it = nullptr;
      chessmans_in.erase(it);
      return;
    }
  }

  throw invalid_argument("any chessman with this id not founded.");
}

shared_ptr<Chessman> User::backChessmanInGame(Chessman::ID id)
{
  for(auto it = chessmans_out.begin(); it != chessmans_out.end(); it++)
  {
    if((*it)->getID() == id)
    {
      chessmans_in.push_back(*it);
      *it = nullptr;
      chessmans_out.erase(it);
      return chessmans_in.back();
    }
  }
  throw invalid_argument("Any chessman with this id not founded.");
}

Chessman::ID User::getKingID() const
{
  for(auto const & item: chessmans_in)
    if(item->getID()[0] == 'K')
        return item->getID();

  throw runtime_error("King not founded.");
}

User::~User()
{
  cnt--;
  for(auto & item: chessmans_in)
    item.reset();

  for(auto & item: chessmans_out)
    item.reset();
  users[cnt] = nullptr;
}

void User::addToChessmansIn(std::shared_ptr<Chessman> chess_man)
{
   chessmans_in.push_back(chess_man);
}

shared_ptr<Chessman> User::removePawnsReach()
{
  chessmans_in.push_back(pawns_reach_last.back());
  pawns_reach_last.pop_back();

  return chessmans_in.back();
}

User::Score User::decNegativeScore(Score score)
{
    return this->negative_score -= score;
}

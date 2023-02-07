#include "../include/User.hpp"

#include "../include/Bishop.hpp"
#include "../include/ChessBoard.hpp"
#include "../include/King.hpp"
#include "../include/Knight.hpp"
#include "../include/Pawn.hpp"
#include "../include/Queen.hpp"
#include "../include/Rook.hpp"

#include <stdexcept>

using namespace std;

std::array<User *, 2> User::users = {nullptr, nullptr};
int User::cnt = 0;

User *& User::getInstance(Name name, Color color, Score positive_score, Score negative_score)
{
  if (cnt < 2)
    users[cnt++] = new User(name, color, positive_score, negative_score);

  return users[cnt - 1];
}

User::User(Name name, Color color, Score score, Score negative_score)
{
  setName(name);
  setColor(color);
  setScore(score);
  setNegativeScore(negative_score);
  setChessmansIn();
}

void User::setName(Name name)
{
  this->name = name;
}

User::Name  User::getName() const
{
  return name;
}

void User::setColor(Color color)
{
  this->color = color;
}

User::Color  User::getColor() const
{
  return color;
}

void User::setScore(Score score)
{
  this->score = score;
}

User::Score  User::getScore() const
{
  return score;
}

void User::setNegativeScore(Score score)
{
  this->negative_score = score;
}

User::Score  User::getNegativeScore() const
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

// set for start game
void User::setChessmansIn()
{
  chessmans_in.clear();
  chessmans_in.push_back(shared_ptr<Chessman>(new Rook(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Knight(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Bishop(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Queen(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new King(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Bishop(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Knight(color)));
  chessmans_in.push_back(shared_ptr<Chessman>(new Rook(color)));

  for (int i = 8; i < 16; i++)
  {
    chessmans_in.push_back(shared_ptr<Chessman>(new Pawn(color)));
  }

  string temp_color;
  if (color == Chessman::WHITE)
    temp_color = "W";
  else
    temp_color = "B";

  string file_addres = "qrc:/Assets/Icons/" + temp_color;
  vector<string> names;
  // to prevent initialization bugs
  names.push_back("Rook");
  names.push_back("Knight");
  names.push_back("Bishop");
  names.push_back("Queen");
  names.push_back("King");
  names.push_back("Bishop");
  names.push_back("Knight");
  names.push_back("Rook");

  for (int i = 8; i < 16; i++)
    names.push_back("Pawn");

  for (size_t i = 0; i < chessmans_in.size(); i++)
    chessmans_in[i]->setIcon((file_addres + names[i] + ".png"));
}

User::ChessmansIn  User::getChessmansIn() const
{
  return chessmans_in;
}

User::ChessmansOut  User::getChessmansOut() const
{
  return chessmans_out;
}

shared_ptr<Chessman>  User::getChessman(Chessman::ID id, bool in) const
{
  if (in)
  {
    for (auto const &item : chessmans_in)
      if (item->getID() == id)
        return item;
  }
  else
  {
    for (auto const &item : chessmans_out)
      if (item->getID() == id)
        return item;
  }

  throw invalid_argument("Any Chessman with this id not existed.");
}

// remove Chessman by hit
void User::hitChessman(Chessman::ID id, bool is_pawn_reached)
{
  // find chessman by id
  for (auto chessman = chessmans_in.begin(); chessman != chessmans_in.end(); chessman++)
  {
    if ((*chessman)->getID() == id)
    {
      // if is pawn which reached the last cell
      if (is_pawn_reached)
        pawns_reach_last.push_back(*chessman);

      else
        chessmans_out.push_back(*chessman);

      // remove from in
      chessmans_in.erase(chessman);
      return;
    }
  }
  throw invalid_argument("User::hitChessman: chessman not found.");
}

// return chessman to game
shared_ptr<Chessman> User::backChessmanToGame(Chessman::ID id)
{
  // find chessman by id
  for (auto chessman = chessmans_out.begin(); chessman != chessmans_out.end(); chessman++)
  {
    if ((*chessman)->getID() == id)
    {
      // add in
      chessmans_in.push_back(*chessman);

      // remove from out
      chessmans_out.erase(chessman);

      // return added chessman
      return chessmans_in.back();
    }
  }
  throw invalid_argument("User::backChessmanToGame: chessman not found.");
}

Chessman::ID  User::getKingID() const
{
  for (auto const &item : chessmans_in)
    if (item->getID()[0] == 'K')
      return item->getID();

  throw runtime_error("King not founded.");
}

User::~User()
{
  cnt--;
  for (auto &item : chessmans_in)
    item.reset();

  for (auto &item : chessmans_out)
    item.reset();
  users[cnt] = nullptr;
}

void User::addToChessmansIn(std::shared_ptr<Chessman> chess_man)
{
  chessmans_in.push_back(chess_man);
}

shared_ptr<Chessman> User::restoreLastPawnsReached()
{
  chessmans_in.push_back(pawns_reach_last.back());
  pawns_reach_last.pop_back();

  return chessmans_in.back();
}

User::Score User::decNegativeScore(Score score)
{
  return this->negative_score -= score;
}

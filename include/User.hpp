#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>

#include "Chessman.hpp"

class User // we can only two create object this class
{
public:
  using Color = Chessman::Color;
  using Name = std::string;
  using Score = int;
  using ChessmansIn = std::vector<std::shared_ptr<Chessman>>;
  using ChessmansOut = std::vector<std::shared_ptr<Chessman>>;
  using PawnsReachLast = std::vector<std::shared_ptr<Chessman>>;

  // get and set functions for make Singleton pattern
  static User *&get(Name, Color, Score positive_score = 0, Score negative_score = 0);

  void setName(Name);
  Name getName() const;
  void setColor(Color);
  Color getColor() const;
  void setScore(Score);
  Score getScore() const;
  Score incScore(Score);
  Score decScore(Score);
  void setNegativeScore(Score);
  Score getNegativeScore() const;
  Score incNegativeScore(Score);
  Score decNegativeScore(Score);

  // initialize chessmans for start game
  void setChessmansIn();
  ChessmansIn getChessmansIn() const;
  ChessmansOut getChessmansOut() const;
  std::shared_ptr<Chessman> getChessman(Chessman::ID, bool in) const;

  // hit chessman
  void hitChessman(Chessman::ID, bool chessman_pawn_final_home = false); // Hit chessman
  std::shared_ptr<Chessman> backChessmanInGame(Chessman::ID);            // Undo Chessman in game
  void addToChessmansIn(std::shared_ptr<Chessman>);                      // add chessman to ChessmanIn
  std::shared_ptr<Chessman> removePawnsReach();

  // Operators functions
  Score operator+(Score) const;
  Score operator-(Score) const;
  Score operator+=(Score);
  Score operator-=(Score);

  // get king id
  Chessman::ID getKingID() const;

  // Destructor
  ~User();

private:
  // Constructor is private for Singeleton pattern
  User(Name, Color, Score = 0, Score = 0);

  // Data member

  // for Singeleton pattern
  static std::array<User *, 2> users;
  static int cnt;

  // Normal Data member
  Name name;
  Color color;
  Score score = 0;
  Score negative_score = 0;
  ChessmansIn chessmans_in;
  ChessmansOut chessmans_out;
  PawnsReachLast pawns_reach_last;
};

#endif /* end of include guard: USER_H*/

#ifndef ROOK_H
#define ROOK_H

#include "Chessman.hpp"

class Rook : public Chessman
{
public:
  Rook(Color, Icon = "");
  Rook(const Rook &); // Copy constructor
  ~Rook();

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;

  // Set public functions
  virtual void setIcon(Icon);

  // set and get functons
  void rookMoved();
  bool getMoved() const;
  void rookNotMoved();

private:
  // Data member
  static size_t cnt;
  bool moved = false;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: ROOK_H*/

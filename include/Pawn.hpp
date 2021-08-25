#ifndef PAWN_H
#define PAWN_H

#include "Chessman.hpp"

class Pawn : public Chessman
{
public:
  Pawn(Color, Icon = "");
  Pawn(const Pawn&     ); // Copy constructor

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;

  // Set public functions
  virtual void setIcon(Icon);


private:
  static size_t cnt;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: PAWN_H*/

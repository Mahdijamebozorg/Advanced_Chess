#ifndef PAWN_H
#define PAWN_H

#include "Chessman.hpp"

class Pawn : public Chessman
{
public:
  // Constructor
  Pawn(Color       );
  Pawn(const Pawn &); // Copy constructor


  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;


private:
  static size_t cnt;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: PAWN_H*/

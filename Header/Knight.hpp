#ifndef KNIGHT_H
#define KNIGHT_H

#include "Chessman.hpp"

class Knight : public Chessman
{
public:
  // Constructor
  Knight(Color         );
  Knight(const Knight &); // Copy constructor

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;


private:
  // Data member
  static size_t cnt;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: KNIGHT_H*/
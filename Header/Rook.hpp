#ifndef ROOK_H
#define ROOK_H

#include "Chessman.hpp"

class Rook : public Chessman
{
public:
  // Constructor
  Rook(Color       );
  Rook(const Rook &); // Copy constructor

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;


private:
  // Data member
  static size_t cnt;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: ROOK_H*/

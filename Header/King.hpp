#ifndef KING_H
#define KING_H

#include "Chessman.hpp"

class King : public Chessman
{
public:
  // Constructor
  King(Color       );
  King(const King &); // Copy constructor


  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;


private:
  static size_t cnt;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: KING_H*/

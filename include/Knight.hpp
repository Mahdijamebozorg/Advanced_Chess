#ifndef KNIGHT_H
#define KNIGHT_H

#include "Chessman.hpp"

class Knight : public Chessman
{
public:
  Knight(Color, Icon = "");
  Knight(const Knight&   ); // Copy constructor

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;

  // Set public functions
  virtual void setIcon(Icon);

  private:
  static size_t cnt;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: KNIGHT_H*/

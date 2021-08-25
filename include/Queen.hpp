#ifndef QUEEN_H
#define QUEEN_H

#include "Chessman.hpp"

class Queen : public Chessman
{
public:
  // Constructor
  Queen(Color, Icon = "");
  Queen(const Queen&    ); // Copy constructor

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;

  // Set public functions
  virtual void setIcon(Icon);

private:
  // Data member
  static size_t cnt;

  // set functinos
  virtual void setID();
};

#endif /* end of include guard: QUEEN_H*/

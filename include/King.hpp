#ifndef KING_H
#define KING_H

#include "Chessman.hpp"

class King : public Chessman
{
public:
  // Constructor
  King(Color, Icon = "");
  King(const King&     ); // Copy constructor

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const;

  // Set public functions
  virtual void setIcon(Icon);

  // set and get functons
  void kingMoved   ()      ;
  bool getMoved    () const;
  void kingNotMoved()      ;


private:
  static size_t cnt        ;
         bool moved = false;

  virtual void setID();
};

#endif /* end of include guard: KING_H*/

#ifndef BISHOP_H
#define BISHOP_H

#include "Chessman.hpp"

class Bishop : public Chessman

{
public:
    Bishop(Color, Icon = "");
    Bishop(const Bishop &); // Copy constructor

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

#endif /* end of include guard: BISHOP_H*/

#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <list>
#include <string>

class Chessman
{
public:
  // Type alias
  using ID        = std::string                                   ;
  using Index = std::pair<unsigned int, unsigned int>;
  using Icon      = std::string                                   ;

  enum ChessType {PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING}; // for prevent from many dynamic_cast
  enum Color     {WHITE, BLACK}                           ;

  Chessman(Color           );
  Chessman(const Chessman &); // Copy constructor

  // set and get functions
          ChessType getChessType(     ) const    ;
          void      setColor    (Color)          ;
          Color     getColor    (     ) const    ;
  virtual void      setID       (     )       = 0;
          ID        getID       (     ) const    ;
          Icon      getIcon     (     ) const    ;
  virtual void      setIcon     (Icon )       = 0;

  // moves functinos
  virtual std::list<Index> getCellsCanGo(Index) const = 0;

  // Destructor
  virtual ~Chessman();


protected:
  // protected data member
  ChessType chess_type;
  ID        id        ;
  Icon      icon      ;


private:
  // Data member
  Color color;

};

#endif /* end of include guard: CHESSMAN_H*/

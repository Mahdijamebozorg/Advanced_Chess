#ifndef CELL_H
#define CELL_H

#include <memory>

#include "Chessman.hpp"

class Cell
{
public:
    // Type alias
    using ChessPieces = std::shared_ptr<Chessman>;

    enum Color { WHITE, BLACK };

    // Constructor
    Cell(); // Defatult Constructo
    Cell(Color, const ChessPieces & = nullptr);
    Cell(const Cell &) = delete; // Copy Constructor
    Cell(Cell &&) = delete;      // Move Constructor

    // set and get functions
    void setChessPieces(
        const ChessPieces &); // When chessman move cell to this cell from other cell or for begin play
    ChessPieces getChessPieces() const;
    void moveChessPieces(Cell &);  // When chessman move from this cell to other cell
    Chessman::ID hitChessPieces(); // Hit chessman by ohter chessman this function remove chessman
    void setColor(Color);
    Color getColor() const;
    Chessman::Icon getIcon() const;

    // Check full or notfull
    bool isFull() const;

    // Operator functions
    const Cell &operator=(const Cell &) = delete; // Assignment operator
    const Cell &operator=(Cell &&) = delete;      // Move assignment operator

    // Converstion Operator
    operator bool() const;

private:
  // data member
  ChessPieces chess_pieces        ;
  Color       color        = BLACK;

};

#endif /* end of include guard: CELL_H*/

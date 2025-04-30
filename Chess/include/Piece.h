#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
class Board; // Forward declaration

class Piece {
protected:
    bool isWhite;
    // check if initialized here or in c'tor :    
    bool alive;              // true if piece is still on the board
    char symbol;             // piece symbol (e.g. 'R' or 'k')

public:
    // Construct with color and optional symbol
    Piece(bool isWhite) : isWhite(isWhite) {}

    // Virtual destructor
    virtual ~Piece() = default;

    // Pure virtual function for movement logic
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const = 0;

    // Accessors
    inline char getSymbol() const { return symbol; }
    inline bool getIsWhite() const { return isWhite; }
    inline bool isAlive() const { return alive; }

    // Mutators
    inline void setAlive(bool status) { alive = status; }
    inline void setSymbol(char s) { symbol = s; }
};

#endif // PIECE_H

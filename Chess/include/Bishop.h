#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Board.h"
#include <cmath> // for abs


class Bishop : public Piece {
public:
    // Constructor assigns appropriate symbol
    Bishop(bool isWhite);

    // Override movement rule
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
};

#endif // BISHOP_H
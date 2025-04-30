#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    // Constructor assigns appropriate symbol
    Rook(bool isWhite);

    // Override movement rule
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
};

#endif // ROOK_H


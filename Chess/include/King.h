#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"


class King : public Piece {
public:
    // Constructor assigns appropriate symbol
    King(bool isWhite);

    // Override movement rule
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
    bool isChess(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const;
    bool isCheckMate(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const;
    bool isStaleMate(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const;
};

#endif // KING_H


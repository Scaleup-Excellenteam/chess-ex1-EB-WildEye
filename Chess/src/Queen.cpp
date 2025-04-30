#include "Queen.h"
#include "Board.h"

Queen::Queen(bool isWhite) : Piece(isWhite) {
    symbol = isWhite ? 'Q' : 'q'; // Assign based on color
    alive = true; 
}

bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Queen moves like both a rook and a bishop
    if (srcRow == destRow || srcCol == destCol || abs(srcRow - destRow) == abs(srcCol - destCol)) {
        // Check path is clear
        int rowStep = (destRow - srcRow == 0) ? 0 : (destRow - srcRow) / abs(destRow - srcRow); // step in row direction
        int colStep = (destCol - srcCol == 0) ? 0 : (destCol - srcCol) / abs(destCol - srcCol); // same for column

        int row = srcRow + rowStep; 
        int col = srcCol + colStep;

        while (row != destRow || col != destCol) {
            if (board.getPiece(row, col) != nullptr)
                return false; // path blocked
            row += rowStep;
            col += colStep;
        }

        // Valid queen move
        return true;
    }
    return false; // Not a valid move
}


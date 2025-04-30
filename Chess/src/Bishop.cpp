#include "Bishop.h"
#include "Board.h"


Bishop::Bishop(bool isWhite) : Piece(isWhite) {
    symbol = isWhite ? 'B' : 'b'; // Assign based on color
    alive = true; 
}

bool Bishop::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Bishop moves diagonally
    if (abs(srcRow - destRow) != abs(srcCol - destCol)) {
        return false; // Not a valid diagonal move
    }

    // Check path is clear
    int rowStep = (destRow - srcRow) / abs(destRow - srcRow); // step in row direction
    int colStep = (destCol - srcCol) / abs(destCol - srcCol); // same for column

    int row = srcRow + rowStep; 
    int col = srcCol + colStep;

    while (row != destRow || col != destCol) {
        if (board.getPiece(row, col) != nullptr) {
            return false; // path blocked
        }
        row += rowStep;
        col += colStep;
    }

    // Valid bishop move
    return true;
}


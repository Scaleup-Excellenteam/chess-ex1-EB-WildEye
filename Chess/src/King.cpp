#include "King.h"
#include "Board.h"

#include <cmath> 
#include <iostream> 

King::King(bool isWhite) : Piece(isWhite) {
    symbol = isWhite ? 'K' : 'k'; // Assign based on color
    alive = true; 
}

bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // King moves one square in any direction
    if (abs(srcRow - destRow) <= 1 && abs(srcCol - destCol) <= 1) {
        return true;
    }
    return false;
}

bool King::isChess(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move puts the king in check
    {
        Piece* targetPiece = board.getPiece(destRow, destCol);
        if (targetPiece != nullptr && targetPiece->getIsWhite() != isWhite) {
            // Check if the target piece can attack the king
            if (targetPiece->isValidMove(destRow, destCol, srcRow, srcCol, board)) {
                return true; // King is in check
            }
        }
    }
    return false; // King is not in check
}

bool King::isCheckMate(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the king is in check and has no valid moves
    if (isChess(srcRow, srcCol, destRow, destCol, board)) {
        for (int row = -1; row <= 1; ++row) {
            for (int col = -1; col <= 1; ++col) {
                if (row == 0 && col == 0) continue; // Skip the current position
                int newRow = srcRow + row;
                int newCol = srcCol + col;
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    if (!isChess(newRow, newCol, destRow, destCol, board)) {
                        return false; // King has a valid move
                    }
                }
            }
        }
        return true; // King is in checkmate
    }
    return false; // King is not in checkmate
}

bool King::isStaleMate(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the king is not in check and has no valid moves
    if (!isChess(srcRow, srcCol, destRow, destCol, board)) {
        for (int row = -1; row <= 1; ++row) {
            for (int col = -1; col <= 1; ++col) {
                if (row == 0 && col == 0) continue; // Skip the current position
                int newRow = srcRow + row;
                int newCol = srcCol + col;
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    if (!isChess(newRow, newCol, destRow, destCol, board)) {
                        return false; // King has a valid move
                    }
                }
            }
        }
        return true; // King is in stalemate
    }
    return false; // King is not in stalemate
}



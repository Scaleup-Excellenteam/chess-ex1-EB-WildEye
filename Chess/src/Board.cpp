// Board.cpp
#include "Board.h"

Board::Board() {
    // No need to prepopulate the map - default c'tor
}

Piece* Board::getPiece(int row, int col) const {
    auto it = grid.find({row, col});
    return (it != grid.end()) ? it->second.get() : nullptr; // Return nullptr if not found, using get() to avoid copying
}

void Board::setPiece(int row, int col, std::unique_ptr<Piece> piece) {
    grid[{row, col}] = std::move(piece); 
}

std::unique_ptr<Piece> Board::removePiece(int row, int col) {
    auto it = grid.find({row, col});
    if (it == grid.end()) return nullptr;

    std::unique_ptr<Piece> removed = std::move(it->second);
    grid.erase(it);
    return removed;
}

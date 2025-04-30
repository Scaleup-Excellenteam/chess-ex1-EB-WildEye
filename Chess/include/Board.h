// Board.h
#ifndef BOARD_H
#define BOARD_H

#include <map> // using std::map
#include "Piece.h"
#include <memory>


class Board {
private:
    std::map<std::pair<int, int>, std::unique_ptr<Piece>> grid;

public:
    Board();
    Piece* getPiece(int row, int col) const;
    void setPiece(int row, int col, std::unique_ptr<Piece> piece);
    std::unique_ptr<Piece> removePiece(int row, int col);
};

#endif // BOARD_H

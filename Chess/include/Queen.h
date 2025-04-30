#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Board.h"
#include <cmath> // for abs
#include <iostream> // for debugging
#include <string>
#include <vector>
#include <memory>
#include <utility> // for std::pair
#include <map> // for std::map
#include <algorithm> // for std::find_if
#include <stdexcept> // for std::out_of_range

class Queen : public Piece {
public:
    // Constructor assigns appropriate symbol
    Queen(bool isWhite);

    // Override movement rule
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
};

#endif // QUEEN_H
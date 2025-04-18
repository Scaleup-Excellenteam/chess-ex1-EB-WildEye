// Updated GameEngine.h
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Piece.h"
#include "Rook.h"
// #include "Bishop.h"
// #include "Queen.h"
// #include "King.h"
// #include "Board.h"

class GameEngine {
private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;
    std::vector<std::shared_ptr<Piece>> pieces; // Store all created pieces
    bool whiteTurn = true;

public:
    GameEngine(const std::string& boardStr);
    int validateMove(const std::string& input);
};
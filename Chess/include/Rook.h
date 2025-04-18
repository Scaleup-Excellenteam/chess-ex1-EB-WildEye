#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(char s, const std::string& source, const std::string& destination);
    bool isValidMove(const std::string& source, const std::string& destination) const;
};

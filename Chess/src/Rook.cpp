#include "Rook.h"

Rook::Rook(char s, const std::string& source, const std::string& destination)
    : Piece(s, source, destination) {}

bool Rook::isValidMove(const std::string& source, const std::string& destination) const {
    int srcCol = source[0] - 'a';
    int srcRow = source[1] - '1';
    int destCol = destination[0] - 'a';
    int destRow = destination[1] - '1';

    return (srcCol == destCol || srcRow == destRow);
}

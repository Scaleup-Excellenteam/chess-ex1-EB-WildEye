#include "GameEngine.h"

GameEngine::GameEngine() : board(new Board()), codeResponse(0),
                           playerColor("white"), opponentColor("black") {
    initGame();
}

GameEngine::~GameEngine() {
    delete board;
    for (Piece* piece : pieces) {
        delete piece;
    }
}

void GameEngine::initGame() {
    // Add pieces
    pieces.push_back(new Rook(true));
    pieces.push_back(new Rook(true));
    pieces.push_back(new Rook(false));
    pieces.push_back(new Rook(false));
    // pieces.push_back(new King(true));
    // pieces.push_back(new King(false));
    // pieces.push_back(new Queen(true));
    // pieces.push_back(new Queen(false));
    // pieces.push_back(new Bishop(true));
    // pieces.push_back(new Bishop(true));
    // pieces.push_back(new Bishop(false));
    // pieces.push_back(new Bishop(false));

    // Place on board
    board->setPiece(0, 0, std::unique_ptr<Piece>(pieces[0]));
    board->setPiece(0, 7, std::unique_ptr<Piece>(pieces[1]));
    board->setPiece(7, 0, std::unique_ptr<Piece>(pieces[2]));
    board->setPiece(7, 7, std::unique_ptr<Piece>(pieces[3]));

    
    // board->setPiece(0, 4, std::unique_ptr<Piece>(pieces[4]));
    // board->setPiece(7, 4, std::unique_ptr<Piece>(pieces[5]));

    // board->setPiece(0, 3, std::unique_ptr<Piece>(pieces[6]));
    // board->setPiece(7, 3, std::unique_ptr<Piece>(pieces[7]));

    // board->setPiece(0, 2, std::unique_ptr<Piece>(pieces[8]));
    // board->setPiece(0, 5, std::unique_ptr<Piece>(pieces[9]));
    // board->setPiece(7, 2, std::unique_ptr<Piece>(pieces[10]));
    // board->setPiece(7, 5, std::unique_ptr<Piece>(pieces[11]));
}

void GameEngine::setCodeResponse(int code) {
    codeResponse = code;
}

int GameEngine::getCodeResponse() const {
    return codeResponse;
}

int GameEngine::validateMove(std::string input, int playerIsWhite) {
    int srcRow = input[0] - 'a';
    int srcCol = input[1] - '1';
    int destRow = input[2] - 'a';
    int destCol = input[3] - '1';

    if (srcRow < 0 || srcRow >= 8 || srcCol < 0 || srcCol >= 8 ||
        destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
        return 11; // invalid
    }

    Piece* piece = board->getPiece(srcRow, srcCol);
    if (!piece) return 11;
    if (piece->getIsWhite() != playerIsWhite) return 12;
    if (board->getPiece(destRow, destCol) != nullptr) return 13;
    if (!piece->isValidMove(srcRow, srcCol, destRow, destCol, *board)) return 21;

    // Move the piece
    board->setPiece(destRow, destCol, std::unique_ptr<Piece>(piece));
    board->removePiece(srcRow, srcCol);

    return 42; // valid move
}

// valid: 41 is needed - the last movement was legal and cause check
// not valid: 31 is needed - 31 - this movement will cause you checkmate

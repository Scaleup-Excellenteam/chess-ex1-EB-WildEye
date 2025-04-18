#include "GameEngine.h"
#include <cctype>

GameEngine::GameEngine(const std::string& boardStr) {
    board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char ch = boardStr[row * 8 + col];
            if (ch == '#') continue;

            bool isWhite = std::isupper(ch);
            ch = std::tolower(ch);
            std::shared_ptr<Piece> piece = nullptr;

            // switch (ch) {
            //     // case 'r': piece = std::make_shared<Rook>(isWhite); break;
            //     // case 'b': piece = std::make_shared<Bishop>(isWhite); break;
            //     // case 'q': piece = std::make_shared<Queen>(isWhite); break;
            //     // case 'k': piece = std::make_shared<King>(isWhite); break;
            //     // case 'n': Knight
            //     // case 'p': Pawn
            //     default: continue;
            // }

            if (piece) {
                board[row][col] = piece;
                pieces.push_back(piece);
            }
        }
    }
}

int GameEngine::validateMove(const std::string& input) {
    if (input.size() != 4)
        return 11;

    int srcRow = input[0] - 'a';
    int srcCol = input[1] - '1';
    int destRow = input[2] - 'a';
    int destCol = input[3] - '1';

    if (srcRow < 0 || srcRow >= 8 || srcCol < 0 || srcCol >= 8 ||
        destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8)
        return 11;

    auto& piece = board[srcRow][srcCol];
    if (!piece)
        return 11;

    if (piece->getIsWhite() != whiteTurn)
        return 12;

    if (board[destRow][destCol] && board[destRow][destCol]->getIsWhite() == whiteTurn)
        return 13;

    if (!piece->isValidMove(srcRow, srcCol, destRow, destCol, *reinterpret_cast<Board*>(&board)))
        return 21;

    board[destRow][destCol] = piece;
    board[srcRow][srcCol] = nullptr;
    whiteTurn = !whiteTurn;
    return 42;
}

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Board.h"
#include "Rook.h"
// #include "King.h"
// #include "Queen.h"
// #include "Bishop.h"
#include <vector>
#include <string>

class GameEngine {
private:
    Board* board;
    std::vector<Piece*> pieces; // raw pointers for cleanup
    int codeResponse;
    std::string playerColor;
    std::string opponentColor; // check if needed

public:
    GameEngine();
    ~GameEngine();

    void initGame();
    void setCodeResponse(int code);
    int getCodeResponse() const;
    int validateMove(std::string input, int playerIsWhite);
};

#endif // GAMEENGINE_H

#include "GameManager.h"
#include "Chess.h"

// ——— constructor ———
GameManager::GameManager()
  : board(nullptr),
    codeResponse(-1),
    isWhiteTurn_(true)
{
    initGame();
}

// ——— initGame ———
void GameManager::initGame()
{
    /* ~~~ 1. Fresh board ~~~ */
    board = std::make_unique<Board>();

    /* ~~~ 2. Black back rank (row 0) ~~~ */
    board->setPiece(0, 0, std::make_unique<Rook>  (false));
    board->setPiece(0, 1, std::make_unique<Knight>(false));
    board->setPiece(0, 2, std::make_unique<Bishop>(false));
    board->setPiece(0, 3, std::make_unique<Queen> (false));
    board->setPiece(0, 4, std::make_unique<King>  (false));
    board->setPiece(0, 5, std::make_unique<Bishop>(false));
    board->setPiece(0, 6, std::make_unique<Knight>(false));
    board->setPiece(0, 7, std::make_unique<Rook>  (false));

    /* ~~~ 3. Black pawns (row 1) ~~~ */
    for (int c = 0; c < 8; ++c)
        board->setPiece(1, c, std::make_unique<Pawn>(false));

    /* ~~~ 4. White pawns (row 6) ~~~ */
    for (int c = 0; c < 8; ++c)
        board->setPiece(6, c, std::make_unique<Pawn>(true));

    /* ~~~ 5. White back rank (row 7) ~~~ */
    board->setPiece(7, 0, std::make_unique<Rook>  (true));
    board->setPiece(7, 1, std::make_unique<Knight>(true));
    board->setPiece(7, 2, std::make_unique<Bishop>(true));
    board->setPiece(7, 3, std::make_unique<Queen> (true));
    board->setPiece(7, 4, std::make_unique<King>  (true));
    board->setPiece(7, 5, std::make_unique<Bishop>(true));
    board->setPiece(7, 6, std::make_unique<Knight>(true));
    board->setPiece(7, 7, std::make_unique<Rook>  (true));
}



void GameManager::setCodeResponse(int code)
{
    codeResponse = code;
}

int GameManager::getCodeResponse() const
{
    return codeResponse;
}


// ——— isCheck ———
// return true if the current player's king is in check
bool GameManager::isCheck() const
{
    bool whiteToMove = isWhiteTurn_;
    return board->inCheck(whiteToMove);
}

// ——— getInput ———
// simple wrapper to read a move string
std::string GameManager::getInput()
{
    std::string input;
    std::cin >> input;
    return input;
}

// ——— displayBoard ———
// print the board (rank 8 down to 1) using each piece's symbol or “. ”
void GameManager::displayBoard() const
{
    for (int r = 7; r >= 0; --r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board->getPiece(r, c);
            if (p)
                std::cout << p->getSymbol() << ' ';
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
}

void GameManager::applyMove(const std::string& mv)
{
    // convert "e2e4" into indices
    int srcRow = mv[0] - 'a'; // file → row
    int srcCol = mv[1] - '1'; // rank → col
    int dstRow = mv[2] - 'a';
    int dstCol = mv[3] - '1';

    makeMove(srcRow, srcCol, dstRow, dstCol); // engine call
}

// ——— makeMove ———
// validate & apply a move, set the codeResponse, and swap turns on success
void GameManager::makeMove(const std::string& move)
{
    int playerIsWhite = whiteToMove() ? 1 : 0;
    int code = validateMove(move);
    setCodeResponse(code);
    if (code == 42 || code == 41) {

        isWhiteTurn_ = !isWhiteTurn_; // switch turn only on legal moves
    }
}

bool GameManager::makeMove(int srcRow, int srcCol, int destRow, int destCol)
{
    if (!board) return false;

    Piece* moving = board->getPiece(srcRow, srcCol);
    if (!moving) return false;                 // should never happen

    /* Take ownership of the source square’s unique_ptr */
    std::unique_ptr<Piece> tmp = board->removePiece(srcRow, srcCol);

    /* If destination holds an opponent piece, it is automatically deleted
       when we overwrite the unique_ptr in that square. */
    board->setPiece(destRow, destCol, std::move(tmp));
    isWhiteTurn_ = !isWhiteTurn_; // switch turn

    return true;
    
}

// ——— isValidMove ———
// check move legality without mutating the board by looking at generateLegalMoves
int GameManager::validateMove(const std::string& mv) const
{
    if (mv.size()!=4) return 11;

    int sR = mv[0]-'a', sC = mv[1]-'1';
    int dR = mv[2]-'a', dC = mv[3]-'1';
    if (sR<0||sR>=8||sC<0||sC>=8||dR<0||dR>=8||dC<0||dC>=8) return 11;

    Piece* src = board->getPiece(sR,sC);
    if (!src) return 11;                           // no piece
    if (src->getIsWhite()!=isWhiteTurn_) return 12; // opponent’s piece

    if (auto dst = board->getPiece(dR,dC);
        dst && dst->getIsWhite()==src->getIsWhite()) return 13; // own piece

    if (!src->isValidMove(sR,sC,dR,dC,*board)) return 21; // piece-specific rule

    // TODO: if you add king-in-check detection, return 41 here.
    return 42;                                      // legal & safe
}

// ——— isCheckmate ———
// checkmate: side to move is in check and has no legal replies
bool GameManager::isCheckmate() const
{
    bool whiteToMove = isWhiteTurn_;
    if (!board->inCheck(whiteToMove)) return false;
    auto legal = board->generateLegalMoves(whiteToMove);
    return legal.empty();
}

// ——— isStalemate ———
// stalemate: side to move is not in check but has no legal replies
bool GameManager::isStalemate() const
{
    bool whiteToMove = isWhiteTurn_;
    if (board->inCheck(whiteToMove)) return false;
    auto legal = board->generateLegalMoves(whiteToMove);
    return legal.empty();
}


 void GameManager::run()
 {

     /* ~~~ 7. GameManager::run – full game loop ~~~ */
  initGame();                                 // set up board & pieces
    Chess view("Console Chess");                // create the view/UI
 
  while (true) {
        view.draw(*board);                      // show current board
        std::string mv = view.readMove();       // e.g. "e2e4" or "exit"
        if (mv == "exit")                       // user wants to quit
            break;

        int code = validateMove(mv);            // legal? returns 11,12,…,42
        if (code < 40) {                        // <40 are invalid‐move codes
            view.showInvalidMove(code);         // tell the user
            continue;                           // ask again
        }

        applyMove(mv);                          // make the move on the board
    }
}

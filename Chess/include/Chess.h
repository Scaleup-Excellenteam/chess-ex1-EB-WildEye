#pragma once
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

#include <string>
#include "GameManager.h"

using std::cout;
using std::cin; 
using std::endl;
using std::string; 

const int _SIZE = 21;

class Chess {
	unsigned char m_board[_SIZE][_SIZE] = { 0 };
	bool m_turn = true;
	string m_boardString;
	string m_input;
	string m_msg = "\n";
	string m_errorMsg = "\n";
	string m_hint = "\n";
	int m_codeResponse;
	GameManager manager_;



	void clear() const;
	void setFrames();
	void setPieces();
    void syncBoardStringWithBoard();
    void show() const;
    void displayBoard() const;
	void showAskInput() const;
	bool isSame() const;
	bool isValid() const;
	bool isExit() const;
	void excute();
	void doTurn();
	// return game manager instance
	GameManager& getGameManager() { return manager_; }


public:
	Chess(const string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	Chess(const Chess&)=delete;
	Chess& operator=(const Chess&) = delete;
	string getInput();
	void setCodeResponse(int codeResponse);
    int validateMoveViaManager(const std::string &mv) const;

	/* ~~~ Draw the given board state ~~~ */
	void draw(const Board& board);

	/* ~~~ Prompt the user and return a move string (e.g. "e2e4") ~~~ */
	std::string readMove();

	/* ~~~ Notify the view of an invalid move code ~~~ */
	void showInvalidMove(int code);

	/* ~~~ Show final result: checkmate or draw ~~~ */
	void showResult(bool whiteTurn, bool gameOver);
};
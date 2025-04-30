// Chess 
#include "Chess.h"
#include "GameEngine.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	int codeResponse = 0;
	GameEngine game; 
	string res = a.getInput();

	bool turn = true; // true is white


	while (res != "exit")
	{
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not piece at the source  
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/ 
		// get user input, check validation and set the code response
		
		codeResponse = game.validateMove(res, true);
		/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput(); 

	}

	cout << endl << "Exiting " << endl; 
	return 0;
}
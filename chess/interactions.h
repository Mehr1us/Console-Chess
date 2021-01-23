#include <stdlib.h>
#include <vector>
struct Tile;

class interactions
{
public:
	bool WhiteTurn = true; // true = white's move, false = black's move
	Tile sTile = { 0,0 };
	Tile tTile = { 0,0 };
	std::vector<Tile>possibleMoves;
	bool selected = false;
	void askForInput(); //asks for player to select a piece
	void askForTarget(); //asks for player to input detination for the selected piece
	void move(); 
	void calcTargets(); //recalculates the positions that pieces can move to
	void calcPossibleMoves();
	bool noAttackers(int f, int r); //returns true if the given Tile has no ids from the opposing team in attackers<>
	bool canMove(int f, int r);
	bool isInvalid(int f, int r);
	bool isInPMVector();
	//
};



struct Tile;

class interactions
{
public:
	bool WhiteTurn = true; // true = white's move, false = black's move
	Tile sTile;
	bool selected = false;
	void askForInput(); //asks for player to select a piece
	void chkvalidMove(int type); //checks which positions the selected piece can move to
	void askForTarget(); //asks for player to input detination for the selected piece
	int countTarget(); //counts how many tiles on cBoard have target = true
	void calcTargets();
	//
};


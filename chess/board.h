#include <stdlib.h>
#include <vector>

struct Tile;

struct bTile {
	int type = 0; // 0 = empty, 1 = pawn, 2 = king, 3 = queen, 4 = rook, 5 = knight, 6 = bishop
	bool p1 = false; // white
	bool p2 = false; // black
	bool unchanged = true;
	int id;
	std::vector<int>attackers;
};

class board
{
public:
	time_t lastTime = {0};
	bool flip = false;
	bTile cBoard[8][8];
	board();
	bool isOccupied(int file, int rank) {
		if (cBoard[file][rank].type == 0)return false;
		else return true;
	}
	void render(int preview);
	void waitSec();
	bool TileIsUnchanged(int f, int r) {
		return cBoard[f][r].unchanged;
	}
	bool CanCastle() {
		if (TileIsUnchanged(0, 4)) {
			if (TileIsUnchanged(0, 0) || TileIsUnchanged(0, 7)) {
				return true;
			}
		}
		if (TileIsUnchanged(7, 4)) {

			if (TileIsUnchanged(7, 0) || TileIsUnchanged(7, 7)) {
				return true;
			}
		}
	}
	int PieceTeam(int f, int r) {
		if (cBoard[f][r].p1)return 1;
		else if (cBoard[f][r].p2)return 2;
		return 0;
	}
};

extern board b;
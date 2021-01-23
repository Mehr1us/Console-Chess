#include "main.h"
interactions inter;
Log L;

board::board() {
	for (int rank = 0; rank < 8; rank++) {
		//pawns
		cBoard[1][rank].type = 1;
		cBoard[1][rank].id = 9 + rank;
		cBoard[6][rank].type = 1;
	}
	for (int file = 0; file < 2; file++) 
		for (int rank = 0; rank < 8; rank++) {
			cBoard[7 - file][rank].p2 = true;
			cBoard[file][rank].p1 = true;
		}
	{
		cBoard[0][0].type = 4; /*/white rook*/		cBoard[0][0].id = 1;
		cBoard[7][0].type = 4; /*/black rook*/		cBoard[7][0].id = 17;
		cBoard[0][7].type = 4; /*/white rook*/		cBoard[0][7].id = 8;
		cBoard[7][7].type = 4; /*/black rook*/		cBoard[7][7].id = 24;
		cBoard[0][1].type = 5; /*/white knight*/	cBoard[0][1].id = 2;
		cBoard[0][2].type = 6; /*/white bishop*/	cBoard[0][2].id = 3;
		cBoard[0][3].type = 3; /*/white queen*/		cBoard[0][3].id = 4;
		cBoard[0][4].type = 2; /*/white king*/		cBoard[0][4].id = 5;
		cBoard[0][5].type = 6; /*/white bishop*/	cBoard[0][5].id = 6;
		cBoard[0][6].type = 5; /*/white knight*/	cBoard[0][6].id = 7;
		cBoard[7][1].type = 5; /*/black knight*/	cBoard[7][1].id = 18;
		cBoard[7][2].type = 6; /*/black bishop*/	cBoard[7][2].id = 19;
		cBoard[7][3].type = 3; /*/black queen*/		cBoard[7][3].id = 20;
		cBoard[7][4].type = 2; /*/black king*/		cBoard[7][4].id = 21;
		cBoard[7][5].type = 6; /*/black bishop*/	cBoard[7][5].id = 22;
		cBoard[7][6].type = 5; /*/black knight*/	cBoard[7][6].id = 23;
	}
}

/* Piece Ids
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32 black
 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0
 9 10 11 12 13 14 15 16 white
 1  2  3  4  5  6  7  8
*/

void board::render(int preview) {
	if (preview)waitSec();
	system("cls");
	std::string out;
	char charmap[] = { ' ', 'p', 'K', 'Q', 'r', 'k', 'b' };
	char charmapB[] = { ' ', 'i', '@', 'W', 'n', 'h', 'I' };
	char notationA[] = { '1', '2', '3', '4', '5', '6', '7', '8' };
	std::string notationB = "\n\n \t  a b c d e f g h\n\n";
	for (int file = 7; file >= 0; file--) {
		out += notationA[file];
		out += "\t| ";
		for (int rank = 7; rank >= 0; rank--) {
			if (cBoard[file][rank].p1) {
				out += charmap[cBoard[file][rank].type];
			}
			else { 
				out += charmapB[cBoard[file][rank].type];
			}
			out += " ";
		}
		out += "|\n";
	}
	out += notationB;
	std::cout << std::endl << "white pieces {p, K, Q, r, k, b}\np = pawn, K = King, Q = Queen, r = rook, k = knight, b = bishop\n\n";
	std::cout << "black pieces {i, @, W, n, h, I}\ni = pawn, @ = King, W = Queen, n = rook, h = knight, I = bishop\n\n\n";
	std::cout << out;
	inter.calcTargets();
	if(preview == 0)inter.askForInput();
	if (flip)flip = false;
	else flip = true;
}

void board::waitSec() {
	time(&lastTime);
	bool npass = true;
	do {
		time_t now;
		time(&now);
		double diff = difftime(now, lastTime);
		if (diff == 1)npass = false;
	} while (npass);
}
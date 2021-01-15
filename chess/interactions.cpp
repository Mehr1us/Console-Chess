#include "main.h"

void interactions::askForInput() {
	if (WhiteTurn)
		std::cout << "\nIt's White's turn" << std::endl;
	else
		std::cout << "\nIt's Black's turn" << std::endl;
	while (true) {
		std::cout << "\nSelect piece" << std::endl;
		char input[3] = "a0";
		std::cin >> input;
		if (input[0] >= 65 && input[0] <= 72)input[0] += 32;
		sTile.r = int(input[0]) - 97;
		sTile.f = int(input[1]) - 49;
		if (sTile.f >= 0 && sTile.f <= 8 && sTile.r >= 0 && sTile.r <= 8)break;
		else if (!(sTile.f >= 1 && sTile.f <= 8))
			std::cout << "Invalid input for file!" << std::endl;
		else if (!(sTile.r >= 1 && sTile.r <= 8))
			std::cout << "Invalid input for rank!" << std::endl;
	}
	std::cout << "File " << sTile.f << " and Rank " << sTile.r << " selected!" << std::endl;
	chkvalidMove(b.cBoard[sTile.f][sTile.r].type);
	///////////////////////////////////////////////////////////////////////////////
	
	return;
}

void interactions::askForTarget() {

}

int interactions::countTarget() {
	int x = 0;
	for (int f = 0; f < 8; f++) {
		for (int r = 0; r < 8; r++) {
			//if (b.cBoard[f][r].target)x++;
		}
	}
	return x;
}

void interactions::calcTargets() {
	for (int f = 0; f < 8; f++) {
		for (int r = 0; r < 8; r++) {
			b.cBoard[f][r].attackers.clear();
		}
	}
	for (int f = 0; f < 8; f++) {
		for (int r = 0; r < 8; r++) {
			int ID = b.cBoard[f][r].id;
			enum class pieces{
				Null,
				Pawn,
				Rook,
				Knight,
				Bishop,
				Queen,
				King
			}piece;
			piece == pieces::Null;
			bool unchanged = b.cBoard[f][r].unchanged;
			if (ID >= 9 && ID <= 16 || ID >= 25 && ID <= 32)piece = pieces::Pawn;
			if (ID == 1 || ID == 8 || ID == 17 || ID == 24)piece == pieces::Rook;
			if (ID == 2 || ID == 7 || ID == 18 || ID == 23)piece == pieces::Knight;
			if (ID == 3 || ID == 6 || ID == 19 || ID == 22)piece == pieces::Bishop;
			if (ID == 4 || ID == 20)piece == pieces::Queen;
			if (ID == 5 || ID == 21)piece == pieces::King;

			if (piece == pieces::Pawn) {
				int move[2] = { -1, 1 };
				if (b.cBoard[f + move[WhiteTurn]][r].type == 0){
					if (WhiteTurn)b.cBoard[f + move[WhiteTurn]][r].attackers.push_back(ID);
				}
				if (unchanged)
					if (!b.isOccupied(f + 2 * move[WhiteTurn], r)){
						b.cBoard[f + 2 * move[WhiteTurn]][r].attackers.push_back(ID);
					}
				for (int i = 0; i < 2; i++) {
					if (b.cBoard[f + move[WhiteTurn]][r + move[i]].type != 0) {
						if (WhiteTurn) {
							if (b.PieceTeam(f + move[WhiteTurn], r + move[i]) == 2) {
								//b.cBoard[sTile.f + act[WhiteTurn]][sTile.r + act[i]].p1target = true;
							}
						}
						else {
							if (b.cBoard[sTile.f + move[WhiteTurn]][sTile.r + move[i]].p1){
								//b.cBoard[sTile.f + act[WhiteTurn]][sTile.r + act[i]].p2target = true;
							}
						}
					}
				}
			}
		}
	}
}


//void interactions::chkvalidMove(int type)
//{
//	//sTile
//	if (type == 1/*Pawn*/) {
//		int move = -1; if (WhiteTurn)move = 1;
//		if (b.cBoard[sTile.f + move][sTile.r].type == 0){
//			//if (WhiteTurn)b.cBoard[sTile.f + move][sTile.r].p1target = true;
//			//else b.cBoard[sTile.f + move][sTile.r].p2target = true;
//		}
//		if (b.cBoard[sTile.f][sTile.r].unchanged)
//			if (b.cBoard[sTile.f + 2 * move][sTile.r].type == 0){
//				//if (WhiteTurn)b.cBoard[sTile.f + 2 * move][sTile.r].p1target = true;
//				//else b.cBoard[sTile.f + 2 * move][sTile.r].p2target = true;
//			}
//		int act[2] = { -1, 1 };
//		for (int i = 0; i < 2; i++) {
//			if (b.cBoard[sTile.f + act[WhiteTurn]][sTile.r + act[i]].type != 0) {
//				if (WhiteTurn) {
//					if (b.cBoard[sTile.f + act[WhiteTurn]][sTile.r + act[i]].p2) {
//						//b.cBoard[sTile.f + act[WhiteTurn]][sTile.r + act[i]].p1target = true;
//					}
//				}
//				else {
//					if (b.cBoard[sTile.f + act[WhiteTurn]][sTile.r + act[i]].p1){
//						//b.cBoard[sTile.f + act[WhiteTurn]][sTile.r + act[i]].p2target = true;
//					}
//				}
//			}
//		}
//	}
//	else if (type == 2/*King*/) {
//		int move[3] = { 1, 0, -1 };
//		for (int file = 0; file < 3; file++) {
//			for (int rank = 0; rank < 3; rank++) {
//				if (!(file == 1 && rank == 1)) {
//					if (sTile.f + move[file] < 8 && sTile.f + move[file] >= 0) {
//						if (sTile.r + move[rank] < 8 && sTile.r + move[rank] >= 0) {
//							//if (!b.cBoard[sTile.f + move[rank]][sTile.r + move[rank]].p1target && !WhiteTurn || !b.cBoard[sTile.f + move[rank]][sTile.r + move[rank]].p2target && WhiteTurn) {
//							//	if (b.cBoard[sTile.f + move[rank]][sTile.r + move[rank]].p1 && !WhiteTurn || b.cBoard[sTile.f + move[rank]][sTile.r + move[rank]].p2 && WhiteTurn) {
//							//		//shut up, it's easier to read if these 
//							//		//statements are broken into multiple if statements
//							//		//if (WhiteTurn)b.cBoard[sTile.f + move[rank]][sTile.r + move[rank]].p1target = true;
//							//		//else b.cBoard[sTile.f + move[rank]][sTile.r + move[rank]].p2target = true;
//							//	}
//							//}
//						}
//					}
//				}
//			}
//		}
//		if (b.CanCastle()) { /*Don't check for this move if both kings 
//			and their respective rooks have been all moved already*/
//			int moveB[2] = { 7, 0 };
//			if (sTile.f == moveB[WhiteTurn] && sTile.r == 4 && b.TileIsUnchanged(sTile.f, sTile.r)) {
//				//O-O
//				if (b.TileIsUnchanged(moveB[WhiteTurn], 7)) {
//					if (b.TileIsEmpty(moveB[WhiteTurn], 6 && b.TileIsEmpty(moveB[WhiteTurn], 5))) {
//						//b.cBoard[moveB[WhiteTurn]][6].target == true;
//					}
//				}
//				//O-O-O
//				if (b.TileIsUnchanged(moveB[WhiteTurn], 0)) {
//					if (b.TileIsEmpty(moveB[WhiteTurn], 3 && b.TileIsEmpty(moveB[WhiteTurn], 2) && b.TileIsEmpty(moveB[WhiteTurn], 1))) {
//						//b.cBoard[moveB[WhiteTurn]][2].target == true;
//					}
//				}
//			}
//		}
//	}
//	else if (type == 3/*Queen*/) {
//		bool contPos = true; bool contNeg = true;
//		//up/down
//		for (int i = 1; i <= 8; i++) {
//			if (sTile.f + i < 8) {
//				if (b.cBoard[sTile.f + i][sTile.r].type == 0 && contPos) {
//					//if (WhiteTurn)b.cBoard[sTile.f + i][sTile.r].p1target = true;
//					//else b.cBoard[sTile.f + i][sTile.r].p2target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f + i][sTile.r].p2) {
//							//b.cBoard[sTile.f + i][sTile.r].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f + i][sTile.r].p1) {
//							//b.cBoard[sTile.f + i][sTile.r].target = true;
//						}
//					}
//					contPos = false;
//				}
//			}
//			if (sTile.f - i >= 0) {
//				if (b.cBoard[sTile.f - i][sTile.r].type == 0 && contNeg) {
//					//b.cBoard[sTile.f - i][sTile.r].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f - i][sTile.r].p2) {
//							//b.cBoard[sTile.f - i][sTile.r].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f - i][sTile.r].p1) {
//							//b.cBoard[sTile.f - i][sTile.r].target = true;
//						}
//					}
//					contNeg = false;
//				}
//			}
//		}
//		contPos = true; contNeg = true;
//		//left/right
//		for (int i = 1; i <= 8; i++) {
//			if (sTile.r + i < 8) {
//				if (b.cBoard[sTile.f][sTile.r + i].type == 0 && contPos) {
//					//b.cBoard[sTile.f][sTile.r + i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f][sTile.r + i].p2) {
//							//b.cBoard[sTile.f][sTile.r + i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f][sTile.r + i].p1) {
//							//b.cBoard[sTile.f][sTile.r + i].target = true;
//						}
//					}
//					contPos = false;
//				}
//			}
//			if (sTile.r - i >= 0) {
//				if (b.cBoard[sTile.f][sTile.r - i].type == 0 && contNeg) {
//					//b.cBoard[sTile.f][sTile.r - i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f][sTile.r - i].p2) {
//							//b.cBoard[sTile.f][sTile.r - i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f][sTile.r - i].p1) {
//							//b.cBoard[sTile.f][sTile.r - i].target = true;
//						}
//					}
//					contNeg = false;
//				}
//			}
//		}
//		bool cont = true;
//		//top-right
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f + i < 8 && sTile.r + i < 8) {
//				if (b.cBoard[sTile.f + i][sTile.r + i].type == 0 && cont) {
//					//b.cBoard[sTile.f + i][sTile.r + i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f + i][sTile.r + i].p2) {
//							//b.cBoard[sTile.f + i][sTile.r + i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f + i][sTile.r + i].p1) {
//							//b.cBoard[sTile.f + i][sTile.r + i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//		cont = true;
//		//bottom-right
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f - i >= 0 && sTile.r + i < 8) {
//				if (b.cBoard[sTile.f - i][sTile.r + i].type == 0 && cont) {
//					//b.cBoard[sTile.f - i][sTile.r + i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f - i][sTile.r + i].p2) {
//							//b.cBoard[sTile.f - i][sTile.r + i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f - i][sTile.r + i].p1) {
//							//b.cBoard[sTile.f - i][sTile.r + i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//		cont = true;
//		//top-left
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f - i >= 0 && sTile.r - i >= 0) {
//				if (b.cBoard[sTile.f - i][sTile.r - i].type == 0 && cont) {
//					//b.cBoard[sTile.f - i][sTile.r - i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f - i][sTile.r - i].p2) {
//							//b.cBoard[sTile.f - i][sTile.r - i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f - i][sTile.r - i].p1) {
//							//b.cBoard[sTile.f - i][sTile.r - i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//		cont = true;
//		//bottom-left
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f + i < 8 && sTile.r - i >= 0) {
//				if (b.cBoard[sTile.f + i][sTile.r - i].type == 0 && cont) {
//					//b.cBoard[sTile.f + i][sTile.r - i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f + i][sTile.r - i].p2) {
//							//b.cBoard[sTile.f + i][sTile.r - i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f + i][sTile.r - i].p1) {
//							//b.cBoard[sTile.f + i][sTile.r - i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//	}
//	else if (type == 4/*Rook*/) {
//		bool contPos = true; bool contNeg = true;
//		for (int i = 1; i <= 8; i++) {
//			if (sTile.f + i < 8) {
//				if (b.cBoard[sTile.f + i][sTile.r].type == 0 && contPos) {
//					//b.cBoard[sTile.f + i][sTile.r].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f + i][sTile.r].p2) {
//							//b.cBoard[sTile.f + i][sTile.r].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f + i][sTile.r].p1) {
//							//b.cBoard[sTile.f + i][sTile.r].target = true;
//						}
//					}
//					contPos = false;
//				}
//			}
//			if (sTile.f - i >= 0) {
//				if (b.cBoard[sTile.f - i][sTile.r].type == 0 && contNeg) {
//					//b.cBoard[sTile.f - i][sTile.r].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f - i][sTile.r].p2) {
//							//b.cBoard[sTile.f - i][sTile.r].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f - i][sTile.r].p1) {
//							//b.cBoard[sTile.f - i][sTile.r].target = true;
//						}
//					}
//					contNeg = false;
//				}
//			}
//		}
//		contPos = true; contNeg = true;
//		for (int i = 1; i <= 8; i++) {
//			if (sTile.r + i < 8) {
//				if (b.cBoard[sTile.f][sTile.r + i].type == 0 && contPos) {
//					//b.cBoard[sTile.f][sTile.r + i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f][sTile.r + i].p2) {
//							//b.cBoard[sTile.f][sTile.r + i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f][sTile.r + i].p1) {
//							//b.cBoard[sTile.f][sTile.r + i].target = true;
//						}
//					}
//					contPos = false;
//				}
//			}
//			if (sTile.r - i >= 0) {
//				if (b.cBoard[sTile.f][sTile.r - i].type == 0 && contNeg) {
//					//b.cBoard[sTile.f][sTile.r - i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f][sTile.r - i].p2) {
//							//b.cBoard[sTile.f][sTile.r - i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f][sTile.r - i].p1) {
//							//b.cBoard[sTile.f][sTile.r - i].target = true;
//						}
//					}
//					contNeg = false;
//				}
//			}
//		}
//	}
//	else if (type == 5/*Knight*/) {
//	int act[2] = { 1, -1 };
//	int act2[2] = { 2, -2 };
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < 2; j++) {
//				if (b.cBoard[sTile.f + act[i]][sTile.r + act2[j]].type == 0) {
//					if (b.cBoard[sTile.f + act[i]][sTile.r + act2[j]].p2 && WhiteTurn || b.cBoard[sTile.f + act[i]][sTile.r + act2[j]].p1 && !WhiteTurn) {
//						//b.cBoard[sTile.f + act[i]][sTile.r + act2[j]].target = true;
//					}
//				}
//				if (b.cBoard[sTile.f + act2[i]][sTile.r + act[j]].type == 0) {
//					if (b.cBoard[sTile.f + act2[i]][sTile.r + act[j]].p2 && WhiteTurn || b.cBoard[sTile.f + act2[i]][sTile.r + act[j]].p1 && !WhiteTurn) {
//						//b.cBoard[sTile.f + act2[i]][sTile.r + act[j]].target = true;
//					}
//				}
//			}
//		}
//	}
//	else if (type == 6/*Bishop*/) {
//		bool cont = true;
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f + i < 8 && sTile.r + i < 8) {
//				if (b.cBoard[sTile.f + i][sTile.r + i].type == 0 && cont) {
//					//b.cBoard[sTile.f + i][sTile.r + i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f + i][sTile.r + i].p2) {
//							//b.cBoard[sTile.f + i][sTile.r + i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f + i][sTile.r + i].p1) {
//							//b.cBoard[sTile.f + i][sTile.r + i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//		cont = true;
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f - i >= 0 && sTile.r + i < 8) {
//				if (b.cBoard[sTile.f - i][sTile.r + i].type == 0 && cont) {
//					//b.cBoard[sTile.f - i][sTile.r + i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f - i][sTile.r + i].p2) {
//							//b.cBoard[sTile.f - i][sTile.r + i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f - i][sTile.r + i].p1) {
//							//b.cBoard[sTile.f - i][sTile.r + i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//		cont = true;
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f - i >= 0 && sTile.r - i >= 0) {
//				if (b.cBoard[sTile.f - i][sTile.r - i].type == 0 && cont) {
//					//b.cBoard[sTile.f - i][sTile.r - i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f - i][sTile.r - i].p2) {
//							//b.cBoard[sTile.f - i][sTile.r - i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f - i][sTile.r - i].p1) {
//							//b.cBoard[sTile.f - i][sTile.r - i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//		cont = true;
//		for (int i = 1; i < 8; i++) {
//			if (sTile.f + i < 8 && sTile.r - i >= 0) {
//				if (b.cBoard[sTile.f + i][sTile.r - i].type == 0 && cont) {
//					//b.cBoard[sTile.f + i][sTile.r - i].target = true;
//				}
//				else {
//					if (WhiteTurn) {
//						if (b.cBoard[sTile.f + i][sTile.r - i].p2) {
//							//b.cBoard[sTile.f + i][sTile.r - i].target = true;
//						}
//					}
//					else {
//						if (b.cBoard[sTile.f + i][sTile.r - i].p1) {
//							//b.cBoard[sTile.f + i][sTile.r - i].target = true;
//						}
//					}
//					cont = false;
//				}
//			}
//		}
//	}
//	else {
//		std::cout << "Invalid Tile Selected" << std::endl;
//		b.render(0);
//		return;
//	}
//	if (countTarget() == 0) {
//		std::cout << "Selected piece has no possible moves!" << std::endl;
//		b.waitSec();
//		b.render(0);
//	}
//	for (int i = 0; i < 5; i++) {
//		b.render(true);
//	}
//	askForTarget();
//}

//                      ^
//old method, redundant |
#include "main.h"


bool interactions::isInvalid(int f, int r) {
	if (!b.isOccupied(f, r))return true;
	if (WhiteTurn && b.cBoard[f][r].p2 || !WhiteTurn && b.cBoard[f][r].p1)return true;
	return false;
}

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
	std::cout << "File " << sTile.f + 1 << " and Rank " << sTile.r + 1 << " selected!" << std::endl;
	///////////////////////////////////////////////////////////////////////////////
	calcPossibleMoves();
	return;
}

void interactions::calcPossibleMoves() {
	int f = sTile.f;
	int r = sTile.r;
	int ID = b.cBoard[f][r].id;

	for (int file = 0; file < 8; file++) {
		for (int rank = 0; rank < 8; rank++) {
			for (int i = 0; i < b.cBoard[file][rank].attackers.size(); i++) {
				if (b.cBoard[file][rank].attackers[i] == ID && canMove(file, rank)) {
					possibleMoves.push_back({ file,rank });
					break;
				}
			}
		}
	}
	if (isInvalid(f,r)) {
		std::cout << "Invalid Tile Selected" << std::endl;
		b.waitSec();
		b.render(0);
		return;
	}
	else if (possibleMoves.size() == 0) {
		std::cout << "Selected piece has no possible moves!" << std::endl;
		b.waitSec();
		b.render(0);
		return;
	}
	std::cout << "The possible moves are:";
	for (int i = 0; i < possibleMoves.size(); i++) {
		std::cout << char(possibleMoves[i].r + 97) << char(possibleMoves[i].f + 49) << ", ";
	}
	std::cout << std::endl;
	askForTarget();
}

void interactions::askForTarget() {
	while (true) {
		std::cout << "\nSelect target tile" << std::endl;
		char input[3] = "a0";
		std::cin >> input;
		if (input[0] >= 65 && input[0] <= 72)input[0] += 32;
		tTile.r = int(input[0]) - 97;
		tTile.f = int(input[1]) - 49;
		if (!isInPMVector()) {
			std::cout << "Invalid move for selected piece!" << std::endl;
		}
		else if (tTile.f >= 0 && tTile.f <= 8 && tTile.r >= 0 && tTile.r <= 8)break;
		else if (!(tTile.f >= 1 && tTile.f <= 8))
			std::cout << "Invalid input for file!" << std::endl;
		else if (!(tTile.r >= 1 && tTile.r <= 8))
			std::cout << "Invalid input for rank!" << std::endl;
	}
	move();
}

void interactions::move() {
	L.logMove(sTile, tTile, WhiteTurn);
	//sTile is co-ords for selected tile
	//tTile is co-ords for where it's moving
	int ID = b.cBoard[sTile.f][sTile.r].id;
	b.cBoard[sTile.f][sTile.r].id = 0;
	b.cBoard[tTile.f][tTile.r].id = ID;
	int TYPE = b.cBoard[sTile.f][sTile.r].type;
	b.cBoard[sTile.f][sTile.r].type = 0;
	b.cBoard[tTile.f][tTile.r].type = TYPE;
	b.cBoard[sTile.f][sTile.r].unchanged = false;
	b.cBoard[tTile.f][tTile.r].unchanged = false;
	b.cBoard[sTile.f][sTile.r].p1 = false;
	b.cBoard[sTile.f][sTile.r].p2 = false;
	if (WhiteTurn) {
		b.cBoard[tTile.f][tTile.r].p1 = true;
		b.cBoard[tTile.f][tTile.r].p2 = false;
		WhiteTurn = false;
	}
	else {
		b.cBoard[tTile.f][tTile.r].p1 = false;
		b.cBoard[tTile.f][tTile.r].p2 = true;
		WhiteTurn = true;
	}
	b.render(0);
}

bool interactions::isInPMVector() {
	int f = tTile.f;
	int r = tTile.r;
	for (int i = 0; i < possibleMoves.size(); i++) {
		if (possibleMoves[i].f == f && possibleMoves[i].r == r)return true;
	}
	return false;
}

void interactions::calcTargets() {
	for (int f = 0; f < 8; f++) {
		for (int r = 0; r < 8; r++) {
			b.cBoard[f][r].attackers.clear();
		}
	}

	//goes through all pieces and marks the ones they can move/attack on/to (subject to change)
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
			piece = pieces::Null;
			bool unchanged = b.cBoard[f][r].unchanged;
			if (ID >= 9 && ID <= 16 || ID >= 25 && ID <= 32)piece = pieces::Pawn;
			if (ID == 1 || ID == 8 || ID == 17 || ID == 24)piece = pieces::Rook;
			if (ID == 2 || ID == 7 || ID == 18 || ID == 23)piece = pieces::Knight;
			if (ID == 3 || ID == 6 || ID == 19 || ID == 22)piece = pieces::Bishop;
			if (ID == 4 || ID == 20)piece = pieces::Queen;
			if (ID == 5 || ID == 21)piece = pieces::King;

			if (piece == pieces::Pawn) {
				int move[2] = { -1, 1 };
				if (f + move[WhiteTurn] >= 0 && f + move[WhiteTurn] < 8) {
					if (!b.isOccupied(f + move[WhiteTurn], r)) {
						if (WhiteTurn)b.cBoard[f + move[WhiteTurn]][r].attackers.push_back(ID);
					}
				}
				if (unchanged && f + 2 * move[WhiteTurn] >= 0 && f + 2 * move[WhiteTurn] < 8) {
					if (!b.isOccupied(f + 2 * move[WhiteTurn], r)) {
						b.cBoard[f + 2 * move[WhiteTurn]][r].attackers.push_back(ID);
					}
				}
				for (int i = 0; i < 2; i++) {
					int file = f + move[WhiteTurn];
					int rank = r + move[i];
					if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
						if (b.isOccupied(file, rank)) {
							b.cBoard[file][rank].attackers.push_back(ID);
						}
					}
				}
			}
			if (piece == pieces::King) {
				int move[3] = { 1, 0, -1 };
				for (int file = 0; file < 3; file++) {
					for (int rank = 0; rank < 3; rank++) {
						int mFile = f + move[file];
						int mRank = r + move[rank];
						if (!(file == 1 && rank == 1) && mFile < 8 && mFile >= 0 && mRank < 8 && mRank >= 0) 
						{
							if (noAttackers(mFile, mRank)) {
								b.cBoard[mFile][mRank].attackers.push_back(ID);
							}
						}
					}
				}
				if (b.CanCastle()) { /*Don't check for this move if both kings 
					and their respective rooks have been all moved already*/
					int moveB[2] = { 7, 0 };
					if (sTile.f == moveB[WhiteTurn] && sTile.r == 4 && b.TileIsUnchanged(sTile.f, sTile.r)) {
						//O-O
						if (b.TileIsUnchanged(moveB[WhiteTurn], 7)) {
							if (!b.isOccupied(moveB[WhiteTurn], 6) && !b.isOccupied(moveB[WhiteTurn], 5) && noAttackers(moveB[WhiteTurn], 6)) {
								b.cBoard[moveB[WhiteTurn]][6].attackers.push_back(ID);
							}
						}
						//O-O-O
						if (b.TileIsUnchanged(moveB[WhiteTurn], 0)) {
							if (!b.isOccupied(moveB[WhiteTurn], 3) && !b.isOccupied(moveB[WhiteTurn], 2) && !b.isOccupied(moveB[WhiteTurn], 1) && noAttackers(moveB[WhiteTurn], 2)) {
								b.cBoard[moveB[WhiteTurn]][2].attackers.push_back(ID);
							}
						}
					}
				}
			}
			if (piece == pieces::Queen) {
				bool dir[8] = { 1,1,1,1,1,1,1,1 };//n, ne, e, se, s, sw, w, nw
				int move[8][2] = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1} };
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if (dir[j]) {
							int file = f + move[j][0] * i;
							int rank = r + move[j][1] * i;
							if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
								if (!b.isOccupied(file, rank)) {
									b.cBoard[file][rank].attackers.push_back(ID);
								}
								else dir[j] = false;
							}
							else dir[j] = false;
						}
						if (!(dir[0] && dir[1] && dir[2] && dir[3] && dir[4] && dir[5] && dir[6] && dir[7]))break;
					}
					if (!(dir[0] && dir[1] && dir[2] && dir[3] && dir[4] && dir[5] && dir[6] && dir[7]))break;
				}
			}
			if (piece == pieces::Rook) {
				bool dir[4] = { 1,1,1,1,};//n, e, s, w
				int move[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 4; j++) {
						if (dir[j]) {
							int file = f + move[j][0] * i;
							int rank = r + move[j][1] * i;
							if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
								if (!b.isOccupied(file, rank)) {
									b.cBoard[file][rank].attackers.push_back(ID);
								}
								else dir[j] = false;
							}
							else dir[j] = false;
						}
						if (!(dir[0] && dir[1] && dir[2] && dir[3]))break;
					}
					if (!(dir[0] && dir[1] && dir[2] && dir[3]))break;
				}
			}
			if (piece == pieces::Knight) {
				int move[8][2] = { {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,-1}, {-2,1}, {1,-2}, {-1,-2} };
				for (int j = 0; j < 8; j++) {
					int file = f + move[j][0];
					int rank = r + move[j][1];
					if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
						if (!b.isOccupied(file, rank)) {
							b.cBoard[file][rank].attackers.push_back(ID);
						}
					}
				}
			}
			if (piece == pieces::Bishop) {
				bool dir[4] = { 1,1,1,1 };//ne, se, sw, nw
				int move[4][2] = { {1,1}, {-1,1}, {-1,-1},  {1,-1} };
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 4; j++) {
						if (dir[j]) {
							int file = f + move[j][0] * i;
							int rank = r + move[j][1] * i;
							if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
								if (!b.isOccupied(file, rank)) {
									b.cBoard[file][rank].attackers.push_back(ID);
								}
								else dir[j] = false;
							}
							else dir[j] = false;
						}
						if (!(dir[0] && dir[1] && dir[2] && dir[3]))break;
					}
					if (!(dir[0] && dir[1] && dir[2] && dir[3]))break;
				}
			}
		}
	}
}

bool interactions::canMove(int f, int r) {
	if (WhiteTurn) {
		if (b.cBoard[f][r].p2 || !b.isOccupied(f, r)) {
			return true;
		}
	}
	else {
		if (b.cBoard[f][r].p1 || !b.isOccupied(f, r)) {
			return true;
		}
	}
	return false;
}

bool interactions::noAttackers(int f, int r) {
	if (WhiteTurn) {
		for (int i = 0; i < b.cBoard[f][r].attackers.size(); i++) {
			if (b.cBoard[f][r].attackers[i] >= 25)return false;
		}
	}
	else {
		for (int i = 0; i < b.cBoard[f][r].attackers.size(); i++) {
			if (b.cBoard[f][r].attackers[i] < 25)return false;
		}
	}
	return true;
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
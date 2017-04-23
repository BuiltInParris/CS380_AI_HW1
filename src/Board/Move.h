/*
 * Move.h
 *
 *  Created on: Apr 19, 2017
 *      Author: sparris
 */

#include <vector>
#include "Board.h"


class Move {
private:
	Board * board;
	bool checkRight(std::vector<int> location);
	bool checkLeft(std::vector<int> location);
	bool checkUp(std::vector<int> location);
	bool checkDown(std::vector<int> location);
public:
	int piece;

	Move(Board * state, int pieceNum) {
		board = state;
		piece = pieceNum;
	}

	std::vector<char> getMoves();
};




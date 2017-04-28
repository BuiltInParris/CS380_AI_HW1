/*
 * Move.h
 *
 *  Created on: Apr 19, 2017
 *      Author: sparris
 */

#include <vector>


class Move {
public:
	int piece;
	char direction;
	Move * parentMove;

	Move(int pieceNum, char dir, Move * move) {
		piece = pieceNum;
		direction = dir;
		parentMove = move;
	}
};




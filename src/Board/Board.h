/*
 * Board.h
 *
 *  Created on: Apr 19, 2017
 *      Author: sparris
 */

#ifndef SRC_BOARD_BOARD_H_
#define SRC_BOARD_BOARD_H_

#include <vector>
#include "Move.h"


class Board {
private:
	void setDimensions(std::string line);
	bool checkRight(std::vector<int> location, int pieceID);
	bool checkLeft(std::vector<int> location, int pieceID);
	bool checkUp(std::vector<int> location, int pieceID);
	bool checkDown(std::vector<int> location, int pieceID);
public:
	int height;
	int width;
	Move * parentMove;

	Board() {
		width = 0;
		height = 0;
		parentMove = NULL;
	};

	Board(Board * board) {
		width = board->width;
		height = board->height;
		cells = board->cells;
		parentMove = board->parentMove;
	};

	Board(int w, int h, Move * move) {
		width = w;
		height = h;
		parentMove = move;
		for(int i = 0; i < h; i ++)
		{
			std::vector<int> zeroRow(w, 0);
			cells.push_back(zeroRow);
		}
	};

	int getHeight();
	int getWidth();
	void loadGameState(std::string filename);
	std::vector<int> getUniquePieces();
	int setValue(int, int, int);
	int getValue(int, int);
	void printCells();
	bool isSolved();
	std::vector<Move *> getPieceMoves(int pieceID, Move * parentMove);
	std::vector< std::vector<int> > cells;
	void normalizeBoard();
	void swapIdx(int idx1,int idx2);
	static bool compareBoardsIdentical(Board * board1, Board * board2);
};



#endif /* SRC_BOARD_BOARD_H_ */

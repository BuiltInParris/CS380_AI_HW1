/*
 * Board.h
 *
 *  Created on: Apr 19, 2017
 *      Author: sparris
 */

#ifndef SRC_BOARD_BOARD_H_
#define SRC_BOARD_BOARD_H_

#include <vector>


class Board {
private:
	void setDimensions(std::string line);
public:
	int height;
	int width;

	Board() {
		width = 0;
		height = 0;
	};

	Board(Board * board) {
		width = board->width;
		height = board->height;
		cells = board->cells;
	};

	Board(int w, int h) {
		width = w;
		height = h;
		for(int i = 0; i < h; i ++)
		{
			std::vector<int> zeroRow(w, 0);
			cells.push_back(zeroRow);
		}
	};

	int getHeight();
	int getWidth();
	void loadGameState(std::string filename);
	int setValue(int, int, int);
	int getValue(int, int);
	void printCells();
	bool isSolved();
	std::vector< std::vector<int> > cells;
};



#endif /* SRC_BOARD_BOARD_H_ */

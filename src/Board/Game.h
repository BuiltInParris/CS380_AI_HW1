/*
 * Game.h
 *
 *  Created on: Apr 23, 2017
 *      Author: sparris
 */

#include <vector>
#include <deque>
#include "Board.h"


class Game {
private:
	//I thought it was using this shared board state which is why it just kept progressing with moves on the same board after it finished a tree

	bool inBottomBound(std::vector<std::vector<int> > coordinates, Board * board);
	bool inTopBound(std::vector<std::vector<int> > coordinates);
	bool inRightBound(std::vector<std::vector<int> > coordinates, Board * board);
	bool inLeftBound(std::vector<std::vector<int> > coordinates);

public:
	Game() {
		IDDFSNodeCount = 0;
		DFSNodeCount = 0;
		BFSNodeCount = 0;
		IDDFSAnswerLength = 0;
		DFSAnswerLength = 0;
		BFSAnswerLength = 0;
	}
	bool gameComplete(Board * board);
	std::vector<Move *> getAllMoves(Move * parentMove, Board * board);
	Board * applyMove(Move * move, Board * board);
	Board * applyMoveCloning(Move * move, Board * board);
	bool randomWalk(int numberOfMoves, Board * board);
	void breadthFirstSearch(Board * board);
	bool depthFirstSearch(Board * dfsSearch);
	bool iterativeDeepeningSearch(Board * dfsBoard, int limit);
	Board * findUnusedBoard(std::vector <Board *> boards, std::vector<Move *> moves, Board * board);
	bool boardExistsInVector(Board*newBoard, std::vector<Board *> boardsFinished);
	bool boardExistsInDeque(Board*newBoard, std::deque<Board *> boardsInProgress);
	int IDDFSNodeCount;
	int DFSNodeCount;
	int BFSNodeCount;
	int IDDFSAnswerLength;
	int DFSAnswerLength;
	int BFSAnswerLength;

};




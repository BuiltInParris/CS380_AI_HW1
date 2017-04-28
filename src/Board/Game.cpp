#include "Game.h"
#include <stdlib.h>     /* srand, rand */
#include <deque>     /* srand, rand */

using namespace std;

bool Game::gameComplete(Board * board){
	for(int i = 0; i < board->cells.size(); i++)
	{
		for(int j = 0; j <  board->cells.at(i).size(); j++)
		{
			if(board->getValue(j, i) == -1)
			{
				return false;
			}
		}
	}
	return true;
}

vector<Move *> Game::getAllMoves(Move * parentMove, Board * board){
	vector<int> uniquePieces = board->getUniquePieces();
	std::vector<Move *> allPossibleMoves(0);
	for(int i = 0; i < uniquePieces.size(); i++)
	{
		vector<Move *> moves = board->getPieceMoves(uniquePieces.at(i), parentMove);
		allPossibleMoves.insert(allPossibleMoves.end(), moves.begin(), moves.end());

	}

	return allPossibleMoves;
}

vector< vector<int> > getPieceLocations(Board * board, int piece){
	vector< vector<int> > coordinates;
	for(int i = 0; i < board->cells.size(); i++)
	{
		for(int j = 0; j <  board->cells.at(i).size(); j++)
		{
			if(board->getValue(j, i) == piece)
			{
					vector<int> coordinate;
					coordinate.push_back(j);
					coordinate.push_back(i);
					coordinates.push_back(coordinate);
			}
		}
	}

	return coordinates;
}


Board * Game::applyMove(Move * move, Board * board){
	vector< vector<int> > coordinates = getPieceLocations(board, move->piece);
	if(move->direction == 'u'){
		if(inTopBound(coordinates))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				board->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				board->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1) - 1, move->piece);
			}
		}
	} else if (move->direction == 'd'){
		reverse(coordinates.begin(),coordinates.end());
		if(inBottomBound(coordinates, board))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				board->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				board->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1) + 1, move->piece);
			}
		}
	} else if (move->direction == 'l'){
		if(inLeftBound(coordinates))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				board->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				board->setValue(coordinates.at(i).at(0) - 1, coordinates.at(i).at(1), move->piece);
			}
		}
	} else if (move->direction == 'r'){
		reverse(coordinates.begin(),coordinates.end());
		if(inRightBound(coordinates, board))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				board->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				board->setValue(coordinates.at(i).at(0) + 1, coordinates.at(i).at(1), move->piece);
			}
		}
	}
	board->normalizeBoard();
	return board;
}

bool Game::inTopBound(vector<vector<int> > coordinates) {
	for (int i = 0; i < coordinates.size(); i++) {
		if (coordinates.at(i).at(1) - 1 < 0) {
			return false;
		}
	}
	return true;
}

bool Game::inBottomBound(vector<vector<int> > coordinates, Board * board) {
	for (int i = 0; i < coordinates.size(); i++) {
		if (coordinates.at(i).at(1) + 1 >= board->height) {
			return false;
		}
	}
	return true;
}

bool Game::inLeftBound(vector<vector<int> > coordinates) {
	for (int i = 0; i < coordinates.size(); i++) {
		if (coordinates.at(i).at(0) - 1 < 0) {
			return false;
		}
	}
	return true;
}

bool Game::inRightBound(vector<vector<int> > coordinates, Board * board) {
	for (int i = 0; i < coordinates.size(); i++) {
		if (coordinates.at(i).at(0) + 1 >= board->width) {
			return false;
		}
	}
	return true;
}

Board * Game::applyMoveCloning(Move * move, Board * board){

	Board * newBoard = new Board(board);
	vector< vector<int> > coordinates = getPieceLocations(newBoard, move->piece);
	if(move->direction == 'u'){
		if(inTopBound(coordinates))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				newBoard->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				newBoard->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1) - 1, move->piece);
			}
		}
	} else if (move->direction == 'd'){
		reverse(coordinates.begin(),coordinates.end());
		if(inBottomBound(coordinates, board))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				newBoard->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				newBoard->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1) + 1, move->piece);
				//newBoard->printCells();
			}
		}
	} else if (move->direction == 'l'){
		if(inLeftBound(coordinates))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				newBoard->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				newBoard->setValue(coordinates.at(i).at(0) - 1, coordinates.at(i).at(1), move->piece);
			}
		}
	} else if (move->direction == 'r'){
		reverse(coordinates.begin(),coordinates.end());
		if(inRightBound(coordinates, board))
		{
			for(int i = 0; i < coordinates.size(); i++)
			{
				newBoard->setValue(coordinates.at(i).at(0), coordinates.at(i).at(1), 0);
				newBoard->setValue(coordinates.at(i).at(0) + 1, coordinates.at(i).at(1), move->piece);
			}
		}
	}
	newBoard->normalizeBoard();
	return newBoard;
}

bool Game::randomWalk(int numberOfMoves, Board * board)
{
	Move * randomMove;
	for(int i = 0; i < numberOfMoves; i++)
	{
		vector<Move *> moves = getAllMoves(randomMove, board);
		Move * randomMove = moves.at(rand() % moves.size());
		board = applyMove(randomMove, board);
		board->normalizeBoard();
		if(board->isSolved())
		{
			return true;
		}
		board->printCells();
	}
	return false;
}


void Game::breadthFirstSearch(Board * board)
{
	vector <Board *> boardsFinished;
	deque <Board *> boardsInProgress;
	vector<Move *> moves = getAllMoves(NULL, board);

	while(true)
	{
		for(int i = 0; i < moves.size(); i++)
		{
			Board* newBoard = applyMoveCloning(moves.at(i), board);
			newBoard->parentMove = moves.at(i);
			if(! boardExistsInVector(newBoard, boardsFinished) && ! boardExistsInDeque(newBoard, boardsInProgress))
			{
				boardsInProgress.push_back(newBoard);
			}
		}

		BFSNodeCount++;
		boardsFinished.push_back(board);

		board = boardsInProgress.front();

		if(boardsInProgress.size() == 0 || board->isSolved())
		{
			break;
		}

		boardsInProgress.pop_front();

		moves = getAllMoves(board->parentMove, board);
	}
	Move * parentMove = board->parentMove;
	while(parentMove != NULL)
	{
		BFSAnswerLength++;
		printf("(%d,%c)\n", parentMove->piece, parentMove->direction);
		parentMove = parentMove->parentMove;
	}
	printf("%d,%d,\n", board->width, board->height);
	board->printCells();
}

vector <Board *> boardsFinished;
deque <Board *> boardsInProgress;

bool Game::depthFirstSearch(Board * dfsBoard)
{
	Board * board = new Board(dfsBoard); //but I just used a deep copy constructor so I'm not sure
	vector<Move *> moves = getAllMoves(dfsBoard->parentMove, board);

	if(board->isSolved())
	{
		Move * parentMove = board->parentMove;
		while(parentMove != NULL)
		{
			DFSAnswerLength++;
			printf("(%d,%c)\n", parentMove->piece, parentMove->direction);
			parentMove = parentMove->parentMove;
		}
		printf("%d,%d,\n", board->width, board->height);
		board->printCells();
		return true;
	}

	for(int i = 0; i < moves.size(); i++)
	{
		Board* newBoard = applyMoveCloning(moves.at(i), board);

		newBoard->parentMove = moves.at(i);
		if(! boardExistsInVector(newBoard, boardsFinished))
		{
			DFSNodeCount++;
			boardsFinished.push_back(newBoard);
			if(depthFirstSearch(new Board(newBoard))){
				return true;
			}
		}
	}
	return false;
}

bool Game::iterativeDeepeningSearch(Board * dfsBoard, int limit)
{
	Board * board = new Board(dfsBoard); //but I just used a deep copy constructor so I'm not sure
	vector<Move *> moves = getAllMoves(dfsBoard->parentMove, board);


	if(board->isSolved())
	{
		Move * parentMove = board->parentMove;
		while(parentMove != NULL)
		{
			IDDFSAnswerLength++;
			printf("(%d,%c)\n", parentMove->piece, parentMove->direction);
			parentMove = parentMove->parentMove;
		}
		printf("%d,%d,\n", board->width, board->height);
		board->printCells();
		return true;
	}

	if(limit <= 0)
	{
		return false;
	}

	for(int i = 0; i < moves.size(); i++)
	{
		Board* newBoard = applyMoveCloning(moves.at(i), board);
		newBoard->parentMove = moves.at(i);
		if(boardExistsInVector(newBoard, boardsFinished))
		{
			//newBoard->printCells();
			boardsFinished.push_back(newBoard);
			IDDFSNodeCount++;
			if(iterativeDeepeningSearch(new Board(newBoard), limit - 1)){
				return true;
			}
		}
	}

	return false;
}

bool Game::boardExistsInVector(Board*newBoard, vector<Board *> boardsFinished)
{
	for(int i = 0; i < boardsFinished.size(); i++)
	{
		if(Board::compareBoardsIdentical(newBoard, boardsFinished.at(i)))
		{
			return true;
		}
	}
	return false;
}

bool Game::boardExistsInDeque(Board*newBoard, deque<Board *> boardsInProgress)
{
	for(int i = 0; i < boardsInProgress.size(); i++)
	{
		if(Board::compareBoardsIdentical(newBoard, boardsInProgress.at(i)))
		{
			return true;
		}
	}
	return false;
}

Board * Game::findUnusedBoard(vector <Board *> boards, vector<Move *> moves, Board * board)
{
	bool boardUnique = true;
	for(int i = 0; i < moves.size(); i++)
	{
		Move * randomMove = moves.at(i);
		Board * newBoard = applyMoveCloning(randomMove, board);
		for(int j = 0; j < boards.size(); j++)
		{
			newBoard->normalizeBoard();
			if(Board::compareBoardsIdentical(boards.at(j), newBoard))
			{
				boardUnique = false;
			}
		}
		if(boardUnique){
			return newBoard;
		}
	}
	return NULL;
}

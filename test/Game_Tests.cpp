#include "gtest/gtest.h"
#include "Board/Game.h"

using namespace std;

TEST(GameTest, TestGameNotFinished) {
	Board *board = new Board();
	board->loadGameState("level1.txt");

	Game * newGame = new Game();
	bool boardSolved = newGame->gameComplete(board);
	ASSERT_EQ(boardSolved, false);
}

TEST(GameTest, TestGameFinished) {
	Board *board = new Board();
	board->loadGameState("level1_complete.txt");

	Game * newGame = new Game();
	bool boardSolved = newGame->gameComplete(board);
	ASSERT_EQ(boardSolved, true);
}

TEST(GameTest, AllMovesGotten) {
	Board *board = new Board();
	board->loadGameState("level1.txt");

	Game * newGame = new Game();
	vector<Move *> allMoves = newGame->getAllMoves(NULL, board);

	ASSERT_EQ(allMoves.size(), 2);
}


TEST(GameTest, TestApplyMove) {
	Board *board = new Board();
	board->loadGameState("level1.txt");
	board->printCells();

	Game * newGame = new Game();
	vector<Move *> allMoves = newGame->getAllMoves(NULL, board);
	Board * newBoard = newGame->applyMove(allMoves.at(0), board);
	//newBoard->printCells();
	//board->printCells();


	ASSERT_EQ(newBoard->getValue(1, 4), 0);
	ASSERT_EQ(newBoard->getValue(2, 4), 0);
	ASSERT_EQ(newBoard->getValue(1, 5), 9);
	ASSERT_EQ(newBoard->getValue(2, 5), 9);
}


TEST(GameTest, TestApplyMoveCloning) {
	Board *board = new Board();
	board->loadGameState("level1.txt");
	board->printCells();

	Game * newGame = new Game();
	vector<Move *> allMoves = newGame->getAllMoves(NULL, board);
	Board * newBoard = newGame->applyMoveCloning(allMoves.at(0), board);
	newBoard->printCells();
	board->printCells();


	ASSERT_NE(board->getValue(1, 4), newBoard->getValue(1, 4));
	ASSERT_NE(board->getValue(2, 4), newBoard->getValue(2, 4));
	ASSERT_NE(board->getValue(1, 5), newBoard->getValue(1, 5));
	ASSERT_NE(board->getValue(2, 5), newBoard->getValue(2, 5));
}


TEST(GameTest, CompareBoards) {
	Board *board = new Board();
	board->loadGameState("level1.txt");
	board->printCells();

	Game * newGame = new Game();
	vector<Move *> allMoves = newGame->getAllMoves(NULL, board);
	Board * newBoard = newGame->applyMoveCloning(allMoves.at(0), board);

	Board* newIdenticalBoard = new Board(board);


	ASSERT_EQ(Board::compareBoardsIdentical(board, newBoard), false);
	ASSERT_EQ(Board::compareBoardsIdentical(board, newIdenticalBoard), true);
}

TEST(GameTest, RandomWalk) {
	Board *board = new Board();
	board->loadGameState("level1.txt");
	board->printCells();

	Game * newGame = new Game();
	bool endState = newGame->randomWalk(3, board);
}

TEST(GameTest, BreadthFirstSearch)
{
	Board *board = new Board();
	board->loadGameState("easy_level.txt");
	board->normalizeBoard();
	printf("INITIAL:\n");
	board->printCells();

	Game * newGame = new Game();
	clock_t start = clock();
	newGame->breadthFirstSearch(board);
	clock_t end = clock();
	double cpu_time = static_cast<double>(end - start)/CLOCKS_PER_SEC;
	printf("%d %.2f %d\n", newGame->BFSNodeCount, cpu_time, newGame->BFSAnswerLength);
}

//READY FOR IT TO EXPLODE?

TEST(GameTest, DepthFirstSearch)
{
	Board *board = new Board();
	board->loadGameState("easy_level.txt");
	board->normalizeBoard();
	printf("INITIAL:\n");
	board->printCells();

	Game * newGame = new Game();
	clock_t start = clock();
	newGame->depthFirstSearch(board);
	clock_t end = clock();
	double cpu_time = static_cast<double>(end - start)/CLOCKS_PER_SEC;
	printf("%d %.2f %d\n", newGame->DFSNodeCount, cpu_time, newGame->DFSAnswerLength);
}


TEST(GameTest, IterativeDeepeningSearch)
{
	Board *board = new Board();
	board->loadGameState("easy_level.txt");
	board->normalizeBoard();
	printf("INITIAL:\n");
	board->printCells();

	Game * newGame = new Game();
	int depth = 0;

	clock_t start = clock();
	while(!newGame->iterativeDeepeningSearch(board, depth))
	{
		depth++;
	}
	clock_t end = clock();
	double cpu_time = static_cast<double>(end - start)/CLOCKS_PER_SEC;

	printf("%d %.2f %d\n", newGame->IDDFSNodeCount, cpu_time, newGame->IDDFSAnswerLength);
}




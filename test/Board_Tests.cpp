#include "gtest/gtest.h"
#include "Board/Board.h"

using namespace std;

TEST(BoardTest, ZeroMatrixConstructWithDimensions) {
	Board *board = new Board(3, 2, NULL);
	board->printCells();

	ASSERT_EQ(board->width, 3);
	ASSERT_EQ(board->height, 2);
}

TEST(BoardTest, SetsValue) {
	Board *board = new Board(3, 2, NULL);
	board->setValue(0, 0, 1);
	board->printCells();

	ASSERT_EQ(board->getValue(0,0), 1);
}

TEST(BoardTest, TestStateLoader) {
	Board *board = new Board();

	board->loadGameState("level1.txt");
	board->printCells();
	ASSERT_NE(board->getValue(0,0), 0);
	ASSERT_NE(board->height, 0);
}

TEST(BoardTest, CopyConstructorTest) {
	Board *board = new Board();
	board->loadGameState("level1.txt");
	Board *copiedBoard = new Board(board);
	ASSERT_EQ(board->getValue(0,0), copiedBoard->getValue(0,0));
	copiedBoard->setValue(0,0,-1);
	ASSERT_NE(board->getValue(0,0), copiedBoard->getValue(0,0));
}


TEST(BoardTest, BoardSolvedTrue) {
	Board *board = new Board();
	board->loadGameState("level1_complete.txt");
	bool boardSolved = board->isSolved();
	ASSERT_EQ(boardSolved, true);
}


TEST(BoardTest, BoardSolvedFalse) {
	Board *board = new Board();
	board->loadGameState("level1.txt");
	bool boardSolved = board->isSolved();
	ASSERT_EQ(boardSolved, false);
}


TEST(BoardTest, testNormalizeBoard) {
	Board *board = new Board();
	board->loadGameState("level1.txt");
	board->normalizeBoard();

	Board *board2 = new Board();
	board2->loadGameState("level1_alternate.txt");
	board2->normalizeBoard();

	board->printCells();
	board2->printCells();

	ASSERT_EQ(Board::compareBoardsIdentical(board, board2), true);
}

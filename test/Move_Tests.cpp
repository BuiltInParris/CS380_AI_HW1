#include "gtest/gtest.h"
#include "Board/Move.h"
#include <vector>

using namespace std;

TEST(MoveTest, checkTestMoves) {
	Board* board = new Board();
	board->loadGameState("level1.txt");
	Move * move = new Move(board, 9);
	vector<char> possibleDirections = move->getMoves();

	for(int i = 0; i < possibleDirections.size(); i++)
	{
		printf("%c", possibleDirections.at(i));
	}

	std::vector<char> answerDirections;
	answerDirections.push_back('d');
	ASSERT_EQ(possibleDirections.size(), answerDirections.size());

	Move * move2 = new Move(board, 10);
	vector<char> possibleDirections2 = move2->getMoves();
	ASSERT_EQ(possibleDirections.size(), answerDirections.size());

	Move * move3 = new Move(board, 2);
	vector<char> possibleDirections3 = move3->getMoves();
	vector<char> nullAnswerDirections = vector<char>();
	ASSERT_EQ(possibleDirections3.size(), nullAnswerDirections.size());
	Move * move4 = new Move(board, 4);
	vector<char> possibleDirections4 = move4->getMoves();
	ASSERT_EQ(possibleDirections4.size(), nullAnswerDirections.size());
}


TEST(MoveTest, checkEdgeLogicMoves) {

	Board* board = new Board();
	board->loadGameState("levelEdgeTest.txt");
	Move * move = new Move(board, 5);
	vector<char> possibleDirections = move->getMoves();

	Move * move2 = new Move(board, 3);
	vector<char> possibleDirections2 = move2->getMoves();

	Move * move3 = new Move(board, 4);
	vector<char> possibleDirections3 = move3->getMoves();

	Move * move4 = new Move(board, 6);
	vector<char> possibleDirections4 = move4->getMoves();
}

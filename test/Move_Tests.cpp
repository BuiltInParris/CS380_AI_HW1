#include "gtest/gtest.h"
#include "Board/Board.h"
#include <vector>

using namespace std;

TEST(MoveTest, checkTestMoves) {
	Board* board = new Board();
	board->loadGameState("level1.txt");
	vector<Move *>moves = board->getPieceMoves(9, NULL);

	std::vector<Move *> answerMoves;
	answerMoves.push_back(new Move(9, 'd', NULL));
	ASSERT_EQ(moves.size(), answerMoves.size());


	vector<Move *>moves2 = board->getPieceMoves(10, NULL);

	std::vector<Move *> answerMoves2;
	answerMoves2.push_back(new Move(10, 'd', NULL));
	ASSERT_EQ(moves2.size(), answerMoves2.size());

	vector<Move *>moves3 = board->getPieceMoves(2, NULL);

	std::vector<Move *> nullAnswerMoves;
	ASSERT_EQ(moves3.size(), nullAnswerMoves.size());

	vector<Move *> moves4 = board->getPieceMoves(2, NULL);
	ASSERT_EQ(moves4.size(), nullAnswerMoves.size());
}


TEST(MoveTest, checkEdgeLogicMoves) {

	Board* board = new Board();
	board->loadGameState("levelEdgeTest.txt");
	vector<Move *> possibleDirections = board->getPieceMoves(5, NULL);

	vector<Move *> possibleDirections2 = board->getPieceMoves(3, NULL);

	vector<Move *> possibleDirections3 = board->getPieceMoves(4, NULL);

	vector<Move *> possibleDirections4 = board->getPieceMoves(6, NULL);
}

#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "Board.h"

using namespace std;

void Board::printCells(){
	for(int i = 0; i < cells.size(); i++)
	{
		for(int j = 0; j < cells.at(i).size(); j++)
		{
			printf("%d", getValue(j, i));
		}
		printf("\n");
	}
	printf("\n");
}

void Board::loadGameState(string filename){
	string line;
	ifstream myfile ("external/" + filename);

	vector< vector <int> > tempCells;

	if (myfile.is_open())
	{

		if(getline (myfile,line))
		{
			setDimensions(line);
		}

		while ( getline (myfile,line) )
		{
			stringstream ss(line);

			vector<int> result;

			while( ss.good() )
			{
				string substr;
				getline( ss, substr, ',' );
				result.push_back(stoi(substr));
			}
			tempCells.push_back(result);
		}
	}

	cells = tempCells;

	myfile.close();
}


// Get the height and width from the file and set them
void Board::setDimensions(string line)
	{
	stringstream ss(line);
	string substr;
	getline( ss, substr, ',' );
	width = stoi(substr);
	getline( ss, substr, ',' );
	height = stoi(substr);
}

int Board::setValue(int x, int y, int value) {
	cells.at(y).at(x) = value;
	return cells.at(y).at(x);
}

int Board::getValue(int x, int y) {
	return cells.at(y).at(x);
}

bool Board::isSolved()
{
	for(int i = 0; i < cells.size(); i++)
	{
		for(int j = 0; j < cells.at(i).size(); j++)
		{
			if(getValue(j, i) == -1)
			{
				return false;
			}
		}
	}
	return true;
}


vector<int> Board::getUniquePieces()
{
	std::vector<int> pieces(0);
	for(int i = 0; i < cells.size(); i ++)
	{
		vector<int> v = cells.at(i);
		pieces.insert(pieces.end(), v.begin(), v.end());
	}
	sort(pieces.begin(), pieces.end());
	pieces.erase(unique(pieces.begin(), pieces.end()), pieces.end());
	pieces.erase(std::remove(pieces.begin(), pieces.end(), 0), pieces.end());
	pieces.erase(std::remove(pieces.begin(), pieces.end(), 1), pieces.end());
	pieces.erase(std::remove(pieces.begin(), pieces.end(), -1), pieces.end());

	return pieces;
}

vector<Move *> Board::getPieceMoves(int pieceID, Move * parentMove)
{
	vector< vector<int> > pieceLocations;
	vector<char> directions;
	vector<Move *> moves;

	for(int i = 0; i < cells.size(); i++)
	{
		for(int j = 0; j < cells.at(i).size(); j++)
		{
			if(cells.at(i).at(j) == pieceID)
			{
				vector<int>position;
				position.push_back(j);
				position.push_back(i);
				pieceLocations.push_back(position);
			}
		}
	}

	directions.push_back('r');
	for(int k = 0; k < pieceLocations.size(); k++)
	{
		if(!checkRight(pieceLocations.at(k), pieceID)){
			directions.pop_back();
			break;
		}
	}

	directions.push_back('l');
	for(int k = 0; k < pieceLocations.size(); k++)
	{
		if(!checkLeft(pieceLocations.at(k), pieceID)){
			directions.pop_back();
			break;
		}
	}

	directions.push_back('u');
	for(int k = 0; k < pieceLocations.size(); k++)
	{
		if(!checkUp(pieceLocations.at(k), pieceID)){
			directions.pop_back();
			break;
		}
	}

	directions.push_back('d');
	for(int k = 0; k < pieceLocations.size(); k++)
		{
		if(!checkDown(pieceLocations.at(k), pieceID)){
			directions.pop_back();
			break;
		}
	}

	for(int i = 0; i < directions.size(); i++)
	{
		moves.push_back(new Move(pieceID, directions.at(i), parentMove));
	}

	return moves;
}

bool Board::checkRight(vector<int> location, int piece)
{
	if(width > location.at(0) + 1
	&& (getValue(location.at(0) + 1, location.at(1)) == 0 ||
	   getValue(location.at(0) + 1, location.at(1)) == piece ||
	   (piece == 2 && getValue(location.at(0) + 1, location.at(1)) == -1)))
	{
		return true;
	}
	return false;
}

bool Board::checkLeft(vector<int> location, int piece)
{
	if(location.at(0) - 1 >= 0
	&& (getValue(location.at(0) - 1, location.at(1)) == 0 ||
		getValue(location.at(0) - 1, location.at(1)) == piece ||
		   (piece == 2 && getValue(location.at(0) - 1, location.at(1)) == -1)))
	{
		return true;
	}
	return false;
}

bool Board::checkUp(vector<int> location, int piece)
{
	if(location.at(1) - 1 >= 0
			&& (getValue(location.at(0), location.at(1) - 1) == 0 ||
	   getValue(location.at(0), location.at(1) - 1) == piece ||
	   (piece == 2 && getValue(location.at(0), location.at(1) - 1) == -1)))
	{
		return true;
	}
	return false;
}

bool Board::checkDown(vector<int> location, int piece)
{
	if(height > location.at(1) + 1)
	{
		if( getValue(location.at(0), location.at(1) + 1) == 0 ||
			getValue(location.at(0), location.at(1) + 1) == piece ||
			(piece == 2 && getValue(location.at(0), location.at(1) + 1) == -1))
		{
			return true;
		}
	}
	return false;
}

//Puts number in order left to right
void Board::normalizeBoard(){
	int nextIdx = 3;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if (cells[i][j] == nextIdx) {
				nextIdx++;
			} else if (cells[i][j] > nextIdx) {
				swapIdx(nextIdx, cells[i][j]);
				nextIdx++;
			}
		}
	}
}

void Board::swapIdx(int idx1,int idx2) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if (cells[i][j] == idx1) {
				cells[i][j] = idx2;
			} else if (cells[i][j] == idx2) {
				cells[i][j] = idx1;
			}
		}
	}
}


bool Board::compareBoardsIdentical(Board * board1, Board * board2)
{
	if(board1->height != board2->height || board1->width != board2->width)
	{
		printf("DIMENSIONS");
		return false;
	}

	for(int i = 0; i < board1->cells.size(); i++)
	{
		for(int j = 0; j < board1->cells.at(i).size(); j++)
		{
			if(board1->cells.at(i).at(j) != board2->cells.at(i).at(j))
			{
				//printf("COMPARISON ... Value at: %d, %d", board1->cells.at(i).at(j), board2->cells.at(i).at(j));
				return false;
			}
		}
	}

	return true;
}

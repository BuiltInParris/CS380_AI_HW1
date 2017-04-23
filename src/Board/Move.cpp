#include <vector>
#include "Move.h"

using namespace std;

vector<char> Move::getMoves()
{
	vector< vector<int> > cells = board->cells;
	vector< vector<int> > pieceLocations;
	vector<char> directions;

	for(int i = 0; i < cells.size(); i++)
	{
		for(int j = 0; j < cells.at(i).size(); j++)
		{
			if(cells.at(i).at(j) == piece)
			{
				vector<int>position;
				position.push_back(j);
				position.push_back(i);
				pieceLocations.push_back(position);
			}
		}
	}

	for(int i = 0; i < pieceLocations.size(); i++)
	{
		printf("(%d, %d)\n", pieceLocations.at(i).at(0), pieceLocations.at(i).at(1));
	}


	directions.push_back('r');
	for(int k = 0; k < pieceLocations.size(); k++)
	{
		if(!checkRight(pieceLocations.at(k))){
			directions.pop_back();
			break;
		}
	}

	directions.push_back('l');
	for(int k = 0; k < pieceLocations.size(); k++)
	{
		if(!checkLeft(pieceLocations.at(k))){
			directions.pop_back();
			break;
		}
	}

	directions.push_back('u');
	for(int k = 0; k < pieceLocations.size(); k++)
	{
		if(!checkUp(pieceLocations.at(k))){
			directions.pop_back();
			break;
		}
	}

	directions.push_back('d');
	for(int k = 0; k < pieceLocations.size(); k++)
		{
		if(!checkDown(pieceLocations.at(k))){
			directions.pop_back();
			break;
		}
	}

	return directions;
}

bool Move::checkRight(vector<int> location)
{
	if(board->width > location.at(0) + 1
	&& (board->getValue(location.at(0) + 1, location.at(1)) == 0 ||
	   board->getValue(location.at(0) + 1, location.at(1)) == piece))
	{
		return true;
	}
	return false;
}

bool Move::checkLeft(vector<int> location)
{
	if(location.at(0) - 1 >= 0
	&& (board->getValue(location.at(0) - 1, location.at(1)) == 0 ||
		board->getValue(location.at(0) - 1, location.at(1)) == piece))
	{
		return true;
	}
	return false;
}

bool Move::checkUp(vector<int> location)
{
	if(location.at(1) - 1 >= 0
			&& (board->getValue(location.at(0), location.at(1) - 1) == 0 ||
	   board->getValue(location.at(0), location.at(1) - 1) == piece))
	{
		return true;
	}
	return false;
}

bool Move::checkDown(vector<int> location)
{
	if(board->height > location.at(1) + 1
			&& (board->getValue(location.at(0), location.at(1) + 1) == 0 ||
	   board->getValue(location.at(0), location.at(1) + 1) == 0))
	{
		return true;
	}
	return false;
}

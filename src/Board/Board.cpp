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
	cells.at(x).at(y) = value;
	return cells.at(x).at(y);
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

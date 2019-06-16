#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "InputReader.h"


InputReader::InputReader(string fileName) : inputFile(fileName)
{
}


InputReader::~InputReader()
{
}


vector<vector<int>> InputReader:: GetMatrix() 
{
	ifstream ifs(inputFile);
	vector<vector<int>> matrix;

	if (!ifs.is_open())
	{
		cout << "Sorry, input file can not be opened." << endl;
	}
	else
	{
		int dimension;
		ifs >> dimension;

		for (int i = 0; i < dimension; i++)
		{
			vector<int> matrixRaw;
			int elem;

			for (int j = 0; j < dimension; j++)
			{
				ifs >> elem;
				matrixRaw.push_back(elem);
			}

			matrix.push_back(matrixRaw);
		}
		
	}

	return matrix;
}

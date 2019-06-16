#pragma once

#include <vector>
#include <iostream>
using namespace std;

class Matrix
{
private:
	vector<vector<int>> matrix;

	vector<vector<int>> GetMinorMatrix(int x, int y);

	int GetMinor(int x, int y);

	int GetFirstAddend(vector<vector<int>> &matrix);
	int GetSecondAddend(vector<vector<int>> &matrix);
	int GetSingleAddend(vector<vector<int>> &matrix);

public:
	Matrix(vector<vector<int>> &matrixVector);
	~Matrix();

	bool IsNotEmptyMatrix();
	void PrintMatrix();

	vector<vector<int>> GetAdditionMatrix();
};
#pragma once
class Matrix
{
private:
	vector<vector<int>> matrix;
	vector<vector<int>> addMatrix;

	void InitializeAddMatrix(vector<vector<int>> &addMatrix);

	vector<vector<int>> GetMinorMatrix(int x, int y);

	static DWORD WINAPI GetMinor(LPVOID lpParam);

	int GetFirstAddend(vector<vector<int>> &matrix);
	int GetSecondAddend(vector<vector<int>> &matrix);
	int GetSingleAddend(vector<vector<int>> &matrix);

	vector<vector<vector<int>>> Devide(int dimension, int amount);

public:
	Matrix(vector<vector<int>> &matrixVector);
	~Matrix();

	bool IsNotEmptyMatrix();
	void PrintMatrix();

	vector<vector<int>> GetAdditionMatrix();
};

struct MainData {
	vector<vector<int>> newMatrix;
	int x;
	int y;
	Matrix* matrixPtr;
};

struct DataForThread {
	vector<vector<int>> newMatrix;
	vector<vector<int>> portion;
	Matrix* matrixPtr;
};
#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix(vector<vector<int>> &matrixVector) : matrix(matrixVector)
{
}


Matrix::~Matrix()
{
}


bool Matrix::IsNotEmptyMatrix() {

	int dimension = matrix.size();

	if (dimension == 0) {
		return false;
	}
	else {
		for (int i = 0; i < dimension; i++) {
			if (dimension == 0) {
				return false;
			}
		}
		return true;
	}
}


void Matrix::PrintMatrix() {
	int dimension = matrix.size();

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}


vector<vector<int>> Matrix::GetAdditionMatrix() {

	vector<vector<int>> add;
	int dimension = matrix.size();

	for (int i = 0; i < dimension; i++) {
		
		vector<int> additionRaw;

		for (int j = 0; j < dimension; j++) {

			int currMinor = GetMinor(i, j);

			if ((i + j) % 2 != 0) {
				currMinor = (-1) * currMinor;
			}

			additionRaw.push_back(currMinor);
		}

		add.push_back(additionRaw);
	}

	return add;
}


int Matrix::GetMinor(int x, int y) {

	vector<vector<int>> minorMatrix = GetMinorMatrix(x, y);
	int minor = 0;
	int dimension = minorMatrix.size();

	if (dimension > 2) {
		int firstAddend = GetFirstAddend(minorMatrix);
		int secondAddend = GetSecondAddend(minorMatrix);
		minor = firstAddend - secondAddend;
	}
	else {
		minor = GetSingleAddend(minorMatrix);	
	}

	return minor;
}


int Matrix::GetFirstAddend(vector<vector<int>> &matrix) {

	int resultAddend = 0;
	int startIndex = 0;
	int dimension = matrix.size();

	for (int i = 0; i < dimension; i++) {

		int positionIndex = startIndex;
		int currAddend = 1;

		for (int j = 0; j < dimension; j++) {

			currAddend = currAddend * matrix[j][positionIndex];

			positionIndex++;

			if (positionIndex >= dimension) {
				positionIndex = 0;
			}
		}

		startIndex++;
		resultAddend += currAddend;
	}

	return resultAddend;
}


int Matrix::GetSecondAddend(vector<vector<int>> &matrix) {

	int resultAddend = 0;
	int dimension = matrix.size();
	int startIndex = dimension - 1;

	for (int i = 0; i < dimension; i++) {

		int positionIndex = startIndex;
		int currAddend = 1;

		for (int j = 0; j < dimension; j++) {

			currAddend = currAddend * matrix[j][positionIndex];

			positionIndex--;

			if (positionIndex < 0) {
				positionIndex = dimension - 1;
			}

		}

		startIndex--;
		resultAddend += currAddend;
	}

	return resultAddend;
}


int Matrix::GetSingleAddend(vector<vector<int>> &matrix) {

	int resultAddend = 0;
	int dimension = matrix.size();

	if (dimension == 1) {
		resultAddend = matrix[0][0];
	}
	else {
		resultAddend = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	return resultAddend;
}


vector<vector<int>> Matrix::GetMinorMatrix(int x, int y) {

	vector<vector<int>> minorMatrix;

	int dimension = matrix.size();

	for (int i = 0; i < dimension; i++) {

		vector<int> minorMatrixRaw;

		for (int j = 0; j < dimension; j++) {
			if ((i != x) && (j != y)) {
				minorMatrixRaw.push_back(matrix[i][j]);
			}
		}

		if (minorMatrixRaw.size() != 0) {
			minorMatrix.push_back(minorMatrixRaw);
		}
	}

	return minorMatrix;
}
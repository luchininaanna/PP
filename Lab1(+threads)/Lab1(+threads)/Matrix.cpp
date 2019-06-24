#include "stdafx.h"
#include "Matrix.h"
#include "CDataForThread.h"


Matrix::Matrix(vector<vector<int>> &matrixVector, int threadAmount)
{
	matrix = matrixVector;
	threadCount = threadAmount;
}


Matrix::~Matrix()
{
}


void Matrix::InitializeAddMatrix(vector<vector<int>> &addMatrix) {

	int dimension = matrix.size();

	for (int i = 0; i < dimension; i++) {

		vector<int> additionRaw;

		for (int j = 0; j < dimension; j++) {
			additionRaw.push_back(0);
		}

		addMatrix.push_back(additionRaw);
	}
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


vector<vector<vector<int>>> Matrix::Devide(int dimension, int amount) {

	vector<vector<vector<int>>> portions;

	int elementAmount = dimension * dimension;
	int elementAmountInPortion = elementAmount / amount;

	int pairCounter = 0;
	int portionCounter = 0;
	vector<int> pair;
	vector<vector<int>> setOfPair;

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {

			if ((pairCounter >= elementAmountInPortion) && (portionCounter != amount - 1)) {
				portions.push_back(setOfPair);

				setOfPair.clear();

				pairCounter = 0;
				portionCounter++;
			}

			pair.clear();
			pairCounter++;
			pair.push_back(i);
			pair.push_back(j);

			setOfPair.push_back(pair);
		}
	}

	portions.push_back(setOfPair);

	return portions;
}


vector<vector<int>> Matrix::GetAdditionMatrix() {

	MainData matrixForThread;
	matrixForThread.matrixPtr = this;
	InitializeAddMatrix(matrixForThread.newMatrix);

	int dimension = matrix.size();
	HANDLE* hThread = new HANDLE[dimension];
	m_portions = Devide(dimension, threadCount);

	InitializeAddMatrix(newMatrix);

	for (int i = 0; i < threadCount; i++) {
		CDataForThread* currData = new CDataForThread();
		currData->matrixPtr = this;
		currData->index = i;

		hThread[i] = CreateThread(NULL, 2048, &GetMinor, (PVOID)currData, 0, NULL);
	}

	WaitForMultipleObjects(threadCount, hThread, true, INFINITE);
	matrixForThread.newMatrix = newMatrix;

	return matrixForThread.newMatrix;
}


DWORD WINAPI Matrix::GetMinor(LPVOID lpParam) {
	CDataForThread* currData = (CDataForThread*)lpParam;
	Matrix* matrixPtr = currData->matrixPtr;
	int index = currData->index;

	vector<vector<int>> portion = matrixPtr->m_portions[index];
	int size = portion.size();

	for (int k = 0; k < size; k++) {	
		vector<int> pair = portion[k];
		int x = pair[0];
		int y = pair[1];

		vector<vector<int>> minorMatrix = matrixPtr->GetMinorMatrix(x, y);
		
		int minor = 0;
		int dimension = minorMatrix.size();

		if (dimension > 2) {
			int firstAddend = matrixPtr->GetFirstAddend(minorMatrix);
			int secondAddend = matrixPtr->GetSecondAddend(minorMatrix);
			minor = firstAddend - secondAddend;
		}
		else {
			minor = matrixPtr->GetSingleAddend(minorMatrix);
		}

		if ((x + y) % 2 != 0)
			minor = (-1) * minor;

		currData-> matrixPtr -> newMatrix[x][y] = minor;
	}
	
	ExitThread(0);
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

			if (positionIndex < 0)
				positionIndex = dimension - 1;
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
			if ((i != x) && (j != y))
				minorMatrixRaw.push_back(matrix[i][j]);
		}

		if (minorMatrixRaw.size() != 0)
			minorMatrix.push_back(minorMatrixRaw);
	}

	return minorMatrix;
}
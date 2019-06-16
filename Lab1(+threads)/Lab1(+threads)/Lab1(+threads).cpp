
#include "stdafx.h"
#include "InputReader.h"
#include "OutputWriter.h"
#include "Matrix.h"

#include <ctime>


int main(int argc, char* argv[])
{
	unsigned int start_time = clock();

	InputReader reader = InputReader(argv[1]);
	OutputWriter writer = OutputWriter(argv[2]);

	vector<vector<int>> matrixVector = reader.GetMatrix();

	
	Matrix matrix = Matrix(matrixVector);

	if (matrix.IsNotEmptyMatrix()) {
		//matrix.PrintMatrix();

		vector<vector<int>> addMatrix = matrix.GetAdditionMatrix();
		Matrix Add = Matrix(addMatrix);

		cout << endl;
		//Add.PrintMatrix();

		writer.PrintMatrix(addMatrix);
	}
	
	unsigned int end_time = clock();
	double search_time = (double)(end_time - start_time) / 1000;

	cout << "Time (in secinds) = " << search_time << endl;
	system("Pause");

	return 0;
}
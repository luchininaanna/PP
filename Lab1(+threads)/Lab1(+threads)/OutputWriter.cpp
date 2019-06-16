#include "stdafx.h"
#include <fstream>
#include "OutputWriter.h"


OutputWriter::OutputWriter(string fileName) : outputFile(fileName)
{
}


OutputWriter::~OutputWriter()
{
}

void OutputWriter::PrintMatrix(vector<vector<int>> &matrix) {

	ofstream fout;
	fout.open(outputFile);

	int dimension = matrix.size();

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			fout << matrix[i][j] << " ";
		}
		fout << endl;
	}

	fout.close();
}

#pragma once

#include <string>
#include <vector>
using namespace std;

class OutputWriter
{
private:
	string outputFile;
public:
	OutputWriter(string fileName);
	~OutputWriter();

	void PrintMatrix(vector<vector<int>> &matrix);
};


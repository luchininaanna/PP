#pragma once

class OutputWriter
{
private:
	string outputFile;
public:
	OutputWriter(string fileName);
	~OutputWriter();

	void PrintMatrix(vector<vector<int>> &matrix);
};


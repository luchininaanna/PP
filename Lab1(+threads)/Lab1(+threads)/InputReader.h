#pragma once


struct Data{
	vector<vector<int>> matrix;
	int threadAmount;
};

class InputReader
{
private:
	string inputFile;

public:
	InputReader(string fileName);
	~InputReader();

	vector<vector<int>> GetMatrix();
	int GetThreadAmount();
};


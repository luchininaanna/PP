#pragma once



class InputReader
{
private:
	string inputFile;

public:
	InputReader(string fileName);
	~InputReader();

	vector<vector<int>> GetMatrix();
};


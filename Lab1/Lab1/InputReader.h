#pragma once

#include <string>
#include <vector>
using namespace std;

class InputReader
{
private:
	string inputFile;
public:
	InputReader(string fileName);
	~InputReader();

	vector<vector<int>> GetMatrix();
};


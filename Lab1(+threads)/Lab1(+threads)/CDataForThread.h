#pragma once
#include "Matrix.h"

class CDataForThread
{
public:
	CDataForThread();
	int index;
	Matrix* matrixPtr;
	~CDataForThread();
};


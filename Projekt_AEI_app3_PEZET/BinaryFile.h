#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "IFile.h"

using namespace std;

class BinaryFile : public IFile
{
public:
	BinaryFile(const string, const string);
	~BinaryFile();

	virtual FileError Write(const vector<Point>&);
	virtual FileError Read(vector<Point>&);
	virtual FileError Read(Point&, const unsigned long);
};


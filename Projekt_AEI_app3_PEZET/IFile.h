#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
using namespace std;

class IFile
{
protected:
	fstream file;
	string filePath;
	unsigned long length;
	fstream::openmode openMode;
public:
	IFile(const string, const string);
	virtual ~IFile();

	enum FileError
	{
		SUCCESS,
		ACCESS_DENIED,
		OUT_OF_BOUNDS,
		FILE_INVALID
	};

	virtual FileError Write(const vector<Point>&) = 0;
	virtual FileError Read(vector<Point>&) = 0;
	virtual FileError Read(Point&, const unsigned long) = 0;
};


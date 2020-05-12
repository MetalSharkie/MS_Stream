#pragma once
#include <sstream>
#include <vector>
#include "Point.h"
#include "IFile.h"
using namespace std;

class CsvFile : public IFile
{
private:

	void WriteLine(Point);
	vector<string> Split(string, char);

public:

	CsvFile(const string, const string);
	~CsvFile();

	virtual FileError Write(const vector<Point>&);
	virtual FileError Read(vector<Point>&);
	virtual FileError Read(Point&, const unsigned long);
};
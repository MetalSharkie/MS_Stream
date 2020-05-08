#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
class IFile
{
protected:
	std::fstream file;
	std::string filePath;
	unsigned long length;
	std::fstream::openmode openMode;
public:
	IFile(const std::string, const std::string);
	virtual ~IFile();

	enum Error
	{
		SUCCESS,
		ACCESS_DENIED,
		OUT_OF_BOUNDS,
		FILE_INVALID
	};

	virtual Error Write(const std::vector<Point>&) = 0;
	virtual Error Read(std::vector<Point>&) = 0;
	virtual Error Read(Point&, const unsigned long) = 0;
};


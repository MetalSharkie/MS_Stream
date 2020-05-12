#include "BinaryFile.h"

BinaryFile::BinaryFile(const std::string filePath, const std::string mode) : IFile(filePath, mode){}

BinaryFile::~BinaryFile()
{
	file.close();
}

IFile::FileError BinaryFile::Write(const std::vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (openMode & std::fstream::out)
	{
		file.write((const char*)v.data(), v.size() * sizeof(Point));
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

IFile::FileError BinaryFile::Read(std::vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (openMode & std::fstream::in)
	{
		v.clear();
		v.resize(length / sizeof(Point));
		file.seekg(0, std::fstream::beg);
		file.read((char*)v.data(), length); //pyt (dlaczego length jako rozmiar bufora)
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

IFile::FileError BinaryFile::Read(Point& p, const unsigned long idx)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (idx * sizeof(Point) > length)
	{
		retVal = FileError(OUT_OF_BOUNDS);
	}
	else if (openMode & std::fstream::in)
	{
		file.seekg(idx * sizeof(Point));
		file.read((char*)(&p), sizeof(Point));
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

#pragma once
#include <string>
#include "IFile.h"
#include "BinaryFile.h"
#include "CsvFile.h"

using namespace std;

static class FileFactory
{
public:
	static IFile* Open(const string filePath, const string mode);
};


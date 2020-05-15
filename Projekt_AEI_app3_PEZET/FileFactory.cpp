#include "FileFactory.h"

//wyb�r jak b�dziemy traktowa� ten plik w ale�no�ci od rozszerzenia, 
//je�li bin to wtedy traktujemy ten plik BinaryFile`m
//je�li csv to b�dziemy traktowa� ten plik klas� CsvFile 
//mo�na to zrobi� w mainie


IFile* FileFactory::Open(const std::string filePath, const std::string mode)
{
	IFile* file = nullptr;

	if (filePath.substr(filePath.find_last_of(".") + 1) == "bin")
	{
		file = new BinaryFile(filePath, mode + "b");
	}
	else if (filePath.substr(filePath.find_last_of(".") + 1) == "csv")
	{
		file = new CsvFile(filePath, mode);
	}

	return file;
}

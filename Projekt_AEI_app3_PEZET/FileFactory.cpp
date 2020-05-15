#include "FileFactory.h"

//wybór jak bêdziemy traktowaæ ten plik w ale¿noœci od rozszerzenia, 
//jeœli bin to wtedy traktujemy ten plik BinaryFile`m
//jeœli csv to bêdziemy traktowaæ ten plik klas¹ CsvFile 
//mo¿na to zrobiæ w mainie


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

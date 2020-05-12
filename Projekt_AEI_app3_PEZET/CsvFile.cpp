#include "CsvFile.h"
using namespace std;

CsvFile::CsvFile(const string filePath, const string mode) : IFile(filePath, mode){}

CsvFile::~CsvFile()
{
	file.close();
}

IFile::FileError CsvFile::Write(const vector<Point>& vector)
{
	FileError rezultat = FileError(ACCESS_DENIED);
	
	if (openMode & fstream::out)
	{
		file.seekp(length, fstream::beg);

		for (size_t i = 0; i < vector.size(); i++)
		{
			file << vector[i].x << ',' << vector[i].y << ',' << vector[i].z << endl;
		}

		length = file.tellp();
		rezultat = FileError(SUCCESS);
	}

	return rezultat;
}

IFile::FileError CsvFile::Read(vector<Point>& wektor)
{
	FileError rezultat = FileError(ACCESS_DENIED);

	if (openMode & fstream::in)
	{
		wektor.clear();
		file.seekg(0, fstream::beg);

		while (file.tellp() < length - 2)
		{
			string pom;
			file >> pom;
			vector<string> pom_wekt;
			pom_wekt = Split(pom, ',');
			wektor.push_back(Point{ stod(pom_wekt[0]), stod(pom_wekt[1]), stod(pom_wekt[2]) });
		}

		rezultat = FileError(SUCCESS);
	}
	return rezultat;
}

IFile::FileError CsvFile::Read(Point& point, const unsigned long idx)
{
	FileError rezultat = FileError(ACCESS_DENIED);


	if (openMode & fstream::in)
	{
		file.seekg(0, fstream::beg);

		for (unsigned long int i = 0; i < idx; i++)
		{
			file.ignore(length, '\n');
			if (file.eof() || file.tellg() > length - 2)
			{
				return OUT_OF_BOUNDS;
			}
		}
		rezultat = FileError(SUCCESS);
	}

	string pom;
	file >> pom;
	vector <string> pom_wekt = Split(pom, ',');
	point = Point{ stod(pom_wekt[0]), stod(pom_wekt[1]), stod(pom_wekt[2]) };

	return rezultat;
}

void CsvFile::WriteLine(Point point)
{
	file.seekp(length, fstream::beg);
	file << point.x << ',' << point.y << ',' << point.z << endl;
	length = file.tellg();
}

vector<string> CsvFile::Split(string ciag, char separator)
{
	stringstream ss(ciag);
	string it;
	vector<string> rezultat;

	while (getline(ss, it, separator))
	{
		rezultat.push_back(it);
	}

	return rezultat;
}
#include "CsvFile.h"
using namespace std;

CsvFile::CsvFile(const string filePath, const string mode) : IFile(filePath, mode) {}

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
			file << vector[i].x << ',' << vector[i].y << ',' << vector[i].z << endl; //przypisuje file to co cznajduje sie w vectorze
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
		wektor.clear(); //usuwa zawartoœæ wektora, teraz size wektora = 0
		file.seekg(0, fstream::beg);  //ustawia pozycjê wskazówki w file na 0 
		
		//file.tellp() - Returns the position of the current character in the output stream.
		//wskazuje tylko pozycjê na której jest puste miejsce po sotatnim zapisanym znaku w file
		//a raczej pozycjê na któr¹ wskazuje wskazówka, a tutaj jest ona od nowa przesuniêta na 0, 
		//bo u¿yliœmy seekg(0, beg!!!)
		while (file.tellp() < length - 2)   //spoko, lenght jest w konstruktorze w IFile
		{
			string pom; //tworzy string pom
			file >> pom; //wpisuje do pom ten pierwszy wyraz ze string (ustawione wczesniej przez seekg!)
			vector<string> pom_wekt; //tworzy wektor pomocniczy
			pom_wekt = Split(pom, ','); //split jest z csvfile
			//pom-wekt jest sobie przekopiowanym ci¹giem znaków z naszego file (przekopiowane znaki a¿ wskazówka nie napotka ',')
			wektor.push_back(Point{ stod(pom_wekt[0]), stod(pom_wekt[1]), stod(pom_wekt[2]) });
			//stod()-zapisuje nam ten obiekt jako z typem double

			//ten while zapisuje po kolei wartoœci z file do wektora, zapisuje tam pointy(x,y,z)
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
			file.ignore(length, '\n'); //pomijamy wszystko a¿ do przejœcia do kolejnej linijki (iloœæ znaków pominiêtych mo¿e byæ wieloœci lenght)
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
//ogólnie to dzieli "ci¹g" i zwraca to co jest w nim zapisane w postacie vectora "rezultat"
//dziêki czemu mo¿emy ci¹g liczb oddzielonych przecinkiem rzeczywiœcie rozdzieliæ
//i pojedyncze liczby powpisywaæ jako wartoœci w wektorze
{
	stringstream ss(ciag);
	string it;
	vector<string> rezultat;


	//getline() - wybiera znaki z "ss", zapisuje w "it" a¿ nie napotka "separatora"
	//a z tym while, no to getline zwraca 0 jak ju¿ nie ma co oddzielaæ /oddawaæ
	while (getline(ss, it, separator))
	{
		rezultat.push_back(it);
	}

	//zwraca sobie wektor zawieraj¹cy znaki z ss, czyli z podanego jako parametr ci¹gu, przekopiowanego do it
	return rezultat;
}
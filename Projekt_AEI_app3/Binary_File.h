#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "File_Error.h"


class BinaryFile
{
private:
	std::fstream file; //
	std::string filePath;
	unsigned long length;
	std::fstream::openmode openMode;
public:
	BinaryFile(const std::string, const std::string);
	~BinaryFile();

	FileError Write(const std::vector<Point>&);
	FileError Read(std::vector<Point>&);
	FileError Read(Point&, const unsigned long);
};

/*
Stworzyć klasę BinaryFile, która zawiera następujące pola i metody: 
● Strumień pliku
● Nazwa pliku 
● Rozmiar pliku 
● Tryb otwarcia 
● Konstruktor przyjmujący ścieżkę pliku jako std::string i tryb otwarcia pliku jako std::string. 
Na podstawie argumentów konstruktora, zostaje otwarty plik o podanej nazwie, w podanym trybie. 
Konstruktor oblicza rozmiar pliku. ● Destruktor, który zamyka plik. 
● Metoda Write(const std::vector<Point>&) - zapisuje wektor punktów do pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(std::vector<Point>&) - wczytuje do wektora punkty z pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(Point&, int) - wczytuje do struktury Point punkt z pliku o podanym indeksie. Zwraca odpowiedni kod błędu FileError. 
Metoda musi pozwalać na odczyt tylko jednego punktu, nie może odczytywać całego pliku celem znalezienia wybranego punktu. 
Należy unikać wykorzystania pętli for do wczytywania i zapisywania punktów.
*/
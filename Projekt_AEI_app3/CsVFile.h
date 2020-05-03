#pragma once
class CsVFile
{
};

/*Stworzyć klasę CsvFile, która zawiera następujące pola i metody: 
Strumień pliku 
● Nazwa pliku 
● Rozmiar pliku 
● Tryb otwarcia
● Konstruktor przyjmujący ścieżkę pliku jako std::string i tryb otwarcia pliku jako std::string. 
Na podstawie argumentów konstruktora, zostaje otwarty plik o podanej nazwie, w podanym trybie. Konstruktor oblicza rozmiar pliku. 
● Destruktor, który zamyka plik. 
● Metoda Write(const std::vector<Point>&) - zapisuje wektor punktów do pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(std::vector<Point>&) - wczytuje do wektora punkty z pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(Point&, int) - wczytuje do struktury Point punkt z pliku o podanym indeksie. Zwraca odpowiedni kod błędu FileError.  
● Prywatne metody pomocnicze:  
	○ WriteLine(Point) - zapisuje jeden punkt do pliku 
	○ Split(std::string, char) - rozdziela łańcuchy znaków zadanym separatorem (typu char).
*/

vector<string> CsvFile::Split(string str, char delim) { 
	vector<string> result;     
	stringstream ss(str);     
	string item;     
	while (getline(ss, item, delim)) 
	{ 
		result.push_back(item); 
	}     
	return result; }
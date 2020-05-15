#include "FileFactory.h"
#include "IFile.h"
#include <iostream>

int main()
{
	IFile* test = FileFactory::Open("test.csv", "r");

	vector<Point> wektor{}; //tworzy pusty wektor

	test->Read(wektor); //u¿ywa read(wektor) na pliku podanym w mainie

	//podaje wartoœci wektorów od w tych konkretnych x, y, z 
	cout << wektor[0].x << " " << wektor[0].y << " " << wektor[0].z << endl;
	cout << wektor[1].x << " " << wektor[1].y << " " << wektor[1].z << endl;
	cout << wektor[2].x << " " << wektor[2].y << " " << wektor[2].z << endl;
	cout << wektor[3].x << " " << wektor[3].y << " " << wektor[3].z << endl;
	cout << wektor[102].x << " " << wektor[102].y << " " << wektor[102].z << endl;


	//to utworzy plik test2 identyczny z plikiem test, a raczej,
	//utworzy pusty excel sheet o nazwie test 2 i przypisze mu po kolei wartoœci z wektora wektor
	//czyli to, co znajduje sie w pliku test
	//dopisze do istniej¹cego pliku, o ile ten jest w formacie .csv!!!!
	//
	IFile* test_proba = FileFactory::Open("test2.csv", "rw");
	test_proba->Write(wektor);


	return 0;
}
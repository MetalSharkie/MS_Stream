#include "FileFactory.h"
#include <iostream>

int main()
{
	IFile* test = FileFactory::Open("test.csv", "r");

	vector<Point> wektor{};

	test->Read(wektor);

	cout << wektor[0].x << " " << wektor[0].y << " " << wektor[0].z << endl;
	cout << wektor[2].x << " " << wektor[2].y << " " << wektor[2].z << endl;


	return 0;
}
#pragma once
struct Point
{
	Point() : x(0.0), y(0.0), z(0.0) {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	double x, y, z;
};

/*
 W osobnym pliku nag��wkowym stworzy� struktur� danych Point, kt�ra sk�ada si� z p�l typu double x, y, z. 
 i. Zaimplementowa� konstruktor domy�lny struktury Point, kt�ry inicjalizuje domy�lne warto�ci zmiennych x, y, z. 
 ii. Zaimplementowa� konstruktor, kt�ry przyjmuje trzy argumenty typu double x, y, z i przekazuje ich warto�� do odpowiednich 
 p�l struktury Point.
*/
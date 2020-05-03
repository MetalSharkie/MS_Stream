#pragma once
struct Point
{
	Point() : x(0.0), y(0.0), z(0.0) {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	double x, y, z;
};

/*
 W osobnym pliku nag³ówkowym stworzyæ strukturê danych Point, która sk³ada siê z pól typu double x, y, z. 
 i. Zaimplementowaæ konstruktor domyœlny struktury Point, który inicjalizuje domyœlne wartoœci zmiennych x, y, z. 
 ii. Zaimplementowaæ konstruktor, który przyjmuje trzy argumenty typu double x, y, z i przekazuje ich wartoœæ do odpowiednich 
 pól struktury Point.
*/
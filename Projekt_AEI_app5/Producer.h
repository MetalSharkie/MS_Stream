#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>
#include <iostream>
#include "IThread.h"


class Producer : public IThread
{
private:
	std::mutex  p_acm_mtx;	
	std::mutex  p_tru_mtx;
	
	std::vector<double> prod_kolekcja = {}; //kolekcja musi by� zsynchronizowana z mutex!!!	
	//std::thread* prod_thr; //wska�nik do threada stworzonego w mainie?
	//czy on wgl jest tutaj potrzebny?

public:
	void Prod_AccessMethod(std::vector<double> &kolekcja);//poprzez rekurencje przypisuje warto�ci z prod_kolekcjii do podanego nowego wektora kolkcji
	std::vector<double> Prod_AccessMethod(); //zwraca stworzony w �rodku wektor kolekcji z zapisanymi danymi z prod_kolekcji
	void ThreadRoutine(); //zapisuje randomowe liczby do kolekcji
};


//pozostaje zsynchronizowa� wszystko z mutex'em!
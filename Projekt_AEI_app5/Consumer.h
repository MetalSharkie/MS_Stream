#pragma once
#include "IThread.h"
#include "Producer.h"
#include <mutex>
#include <thread>
#include <atomic>
#include <vector>
#include <string>

class Consumer : public IThread
{
private:
	std::mutex c_acm_mtx;
	std::mutex c_tru_mtx;

	double cons_srednia; //tutaj zapisana zostaje ta œrednia obliczona w metodzie thread routine
	std::vector<double> cons_kolekcja = {0};
	//std::thread* cons_thr;
	Producer* P_thr;
public:
	Consumer(Producer* wsk); //no dobra, tylko ¿e tam nie mamy ¿adnego cia³a obiektu w producencie
	void Cons_AccessMethod(double podana_srednia); //ma zwracaæ aktualn¹ wartoœæ sredniej
	double Cons_AccessMethod(); //tutaj te¿ zwraca, tylko ¿e tam przypisuje podanemu a tutaj poprostu dzia³a jako return
	void ThreadRoutine();
};


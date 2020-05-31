#include "Producer.h"
#include <random>
#include <chrono>

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count()); //obtain a seed and put into generator
std::uniform_real_distribution<double> distribution(0.0, 1.0); //now throw it into a distributor

void Producer::Prod_AccessMethod(std::vector<double>& kolekcja)
{//zsynchronizowana metoda dostêpowa zwracaj¹ca aktualnie wygenerowan¹ kolekcjê
	
	kolekcja = prod_kolekcja; //zapisuje do podanej jako referencja kolekcji obecn¹ v_kolekcjê!
	//czy trzeba jeœli jest to wektor, to te¿ trzeba kolkcja[i]=prod_kolekcja[i]?
}

std::vector<double> Producer::Prod_AccessMethod()
{
	p_acm_mtx.lock();
	std::vector<double> zwracana_kolekcja = {};
	zwracana_kolekcja = prod_kolekcja;

	for (size_t i = 0; i < zwracana_kolekcja.size(); i++)
	{
		std::cout << "\t\t\tzwracana_kol [ " << i << " ]= " << zwracana_kolekcja[i] << "\n";
	}

	p_acm_mtx.unlock();
	return zwracana_kolekcja;
	//return prod_kolekcja;
	//mtx.unlock();
}

void Producer::ThreadRoutine()
{	
	double random_number;
	//int permission = 1; 
	//for (int i=0; i<4; i++)
	//IThread::Status::STOPPED;
	//while(permission)	

	while (this->isRunning())	/// isRunning jest funkcj¹ z iThread!, zwraca nam aktualny status threada, czy ten dzia³a czy te¿ nie!
	{
		
		p_tru_mtx.lock();
		random_number = distribution(generator);
		std::cout << "\nrandom_number = " << random_number << "\n\n";

		//random_number = distribution(generator); //creating a random number using distributor from above
		prod_kolekcja.push_back(random_number); //zapisuje t¹ liczbê losow¹ do kolekcji
		p_tru_mtx.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1)); //uœpienie w¹tku na 1sek		
		
	
}
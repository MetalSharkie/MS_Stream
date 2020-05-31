#include "Consumer.h"


Consumer::Consumer(Producer* wsk)
{ //dziêki wkaŸnikowi ustawia wartoœci cons_kolekcji na te z kolekcji obiktu klasy Producent wskazanego przez *wsk
	
	//cons_kolekcja = wsk->Prod_AccessMethod();
	P_thr = wsk;
}

void Consumer::Cons_AccessMethod(double podana_srednia)
{
	podana_srednia = cons_srednia;
}
	
double Consumer::Cons_AccessMethod()
{
	c_acm_mtx.lock();
	double zwracana_srednia = 0;
	zwracana_srednia = cons_srednia;
	c_acm_mtx.unlock();
	return zwracana_srednia;	
}

void Consumer::ThreadRoutine()
{
	size_t j = 0;
	double srednia = 0;
	double srednia2 = 0;
	double suma = 0;

	//for(int j=0; j<2;j++)
	while(this->isRunning())
	//while (P_thr)		
	{
		c_tru_mtx.lock();

		cons_kolekcja = P_thr->Prod_AccessMethod(); //musimy co jakiœ czas pobieraæ dane poprzez t¹ metode AccessMethod z obiektu producenta
		std::cout << "cons_kolekcja.size():" << cons_kolekcja.size() << std::endl;

		for (j = 0; j < cons_kolekcja.size(); j++)
		{
			srednia = (srednia + cons_kolekcja[j])/(j+1);
			suma = suma + cons_kolekcja[j];
		
		}	
	srednia2 = (suma /cons_kolekcja.size()); 
	//imho obydwie œrednie dzia³aj¹ niepoprawnie, problem le¿y chyba w tym wspólnym bufferze, wspólnym korzystaniu z kolekcji

	c_tru_mtx.unlock();

	//std::string s(10, '*');	

	cons_srednia = srednia;
	//std::cout << s << std::endl;
	std::cout << "----------------SREDNIA:" << srednia << std::endl;
	std::cout << "-----------------------------SREDNIA__2:" << srednia2 << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1)); //ustawiamy co jaki czas bêdzie to robi³
	}
	
}
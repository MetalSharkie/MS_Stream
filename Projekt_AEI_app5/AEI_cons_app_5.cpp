
#include <iostream>
#include <chrono>
#include <mutex>
#include <vector>
#include "IThread.h"
#include "Producer.h"
#include "Consumer.h"

int main()
{
    std::cout << "Hello my luv!\n";                                        
      
    Producer thr_main_pro;     
    Consumer thr_main_con(&thr_main_pro);
    
    thr_main_pro.Start();    //rozpoczyna thread    
    thr_main_con.Start();

    //thr_main_pro.Join(); //je�li join b�dzie tutaj, to wtedy nie przejdziemy do ifa, a je�li join b�dzie po ifie, to nie mamy po co joinowa�, bo thready s� ju� zastopowane
    //thr_main_con.Join();

   if (std::getchar()) { thr_main_pro.Stop(); thr_main_con.Stop(); } //zewn�trzny callout do thread�w �eby wyj�� z while()`�w w nich
       
    //dobra, imho ten producer podany konsumentowi nie powinien by� chyba podawany jako referencja w konstruktorze. 
    //to chyba dzia�a�oby lepiej je�liwzieliby�my ten konstruktor i wrzucili go 

    thr_main_pro.Join(); //sprawia �e czekamy z przej�ciem dalej w mainie, a� funckje w threadach si� zako�cz�
    thr_main_con.Join(); //czy musimy je joinowa�, je�li one maj� dzia�a� sobie bez przerwy, osobno, bez patrzenia na siebie na wzajem tak jakby?
        

    //1.uruchoni� kilka w�tk�w producent�w i konsument�w
    //2.zweryfikowa� ilo�� w�tk�w uruchomionych przez aplikacj� (w mened�erze zada� systemu)
    //3.zaimplementowa� mechanizm, pozwalaj�cy na oddzia�ywanie z w�tkami:
        // - wy�wietlenie warto�ci �redniej ka�dego z konsument�w
        // - zatrzymanie dzia�ania w�tk�w     
    
    
    
    return 0;

}

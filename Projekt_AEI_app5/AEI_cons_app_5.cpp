
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

    //thr_main_pro.Join(); //jeœli join bêdzie tutaj, to wtedy nie przejdziemy do ifa, a jeœli join bêdzie po ifie, to nie mamy po co joinowaæ, bo thready s¹ ju¿ zastopowane
    //thr_main_con.Join();

   if (std::getchar()) { thr_main_pro.Stop(); thr_main_con.Stop(); } //zewnêtrzny callout do threadów ¿eby wyjœæ z while()`ów w nich
       
    //dobra, imho ten producer podany konsumentowi nie powinien byæ chyba podawany jako referencja w konstruktorze. 
    //to chyba dzia³a³oby lepiej jeœliwzielibyœmy ten konstruktor i wrzucili go 

    thr_main_pro.Join(); //sprawia ¿e czekamy z przejœciem dalej w mainie, a¿ funckje w threadach siê zakoñcz¹
    thr_main_con.Join(); //czy musimy je joinowaæ, jeœli one maj¹ dzia³aæ sobie bez przerwy, osobno, bez patrzenia na siebie na wzajem tak jakby?
        

    //1.uruchoniæ kilka w¹tków producentów i konsumentów
    //2.zweryfikowaæ iloœæ w¹tków uruchomionych przez aplikacjê (w mened¿erze zadañ systemu)
    //3.zaimplementowaæ mechanizm, pozwalaj¹cy na oddzia³ywanie z w¹tkami:
        // - wyœwietlenie wartoœci œredniej ka¿dego z konsumentów
        // - zatrzymanie dzia³ania w¹tków     
    
    
    
    return 0;

}

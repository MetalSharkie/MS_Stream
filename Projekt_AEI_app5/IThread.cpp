#include "IThread.h"


IThread::IThread() : status(IThread::Status::STOPPED), thr(nullptr)
{
}


IThread::~IThread()
{
	//Join();
	Stop();
}

void IThread::Start()
{
	//pocz�tkowo je�li chcemy co� zatrzyma� to musi wczesniej dzia�a�, wi�c je�li thr b�dzie dzia�a� ju� wcze�cniej
	//to b�dzie mia� warto�� tak jakby 1 , wi�c w if b�dzie if(0), co nam nie wystartuje warunku
	if (!thr)
	{
		status = IThread::Status::RUNNING; // czyli w sumie dzi�ki temu threadRoutine da nam 1
		thr = new std::thread(&IThread::ThreadRoutine, this);
		//new std::thread(true, thr);
		//wi�c tak jakby dajemy thr warto�� Running!
		
	}
}

void IThread::Stop()
{
	//odwrotnie do start()
	if (thr)
	{
		status = IThread::Status::STOPPED;
		if (thr->joinable()) thr->join(); //ten if sprawdza czy mo�na joinowa� do thr
		delete thr; //wska�nik jest pami�ci nie ma xD
		thr = nullptr;
	}
}

void IThread::Join()
{//co si� stanie je�li pozamieniasz te kolejno�ci ustawienia statusu i danie join()?
	//je�li nie uda si� zrobi� joina to wtedy wywali nam b�ad i nie zmieni satusu na stopped, 
	//inaczej ni� w Stop()
	if (thr)
	{
		if (thr->joinable()) thr->join();
		status = IThread::Status::STOPPED;
		delete thr;
		thr = nullptr;
	}
}

bool IThread::isRunning() // sprawdzamy czy jest running, je�li jest, to zwr�ci nam 1, je�li nie, to 0
{//true albo false, a pod 1 jest te� zapisany running
	return status == IThread::Status::RUNNING;
}

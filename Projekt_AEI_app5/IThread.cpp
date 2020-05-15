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
	//pocz¹tkowo jeœli chcemy coœ zatrzymaæ to musi wczesniej dzia³aæ, wiêc jeœli thr bêdzie dzia³a³ ju¿ wczeœcniej
	//to bêdzie mia³ wartoœæ tak jakby 1 , wiêc w if bêdzie if(0), co nam nie wystartuje warunku
	if (!thr)
	{
		status = IThread::Status::RUNNING; // czyli w sumie dziêki temu threadRoutine da nam 1
		thr = new std::thread(&IThread::ThreadRoutine, this);
		//new std::thread(true, thr);
		//wiêc tak jakby dajemy thr wartoœæ Running!
		
	}
}

void IThread::Stop()
{
	//odwrotnie do start()
	if (thr)
	{
		status = IThread::Status::STOPPED;
		if (thr->joinable()) thr->join(); //ten if sprawdza czy mo¿na joinowaæ do thr
		delete thr; //wskaŸnik jest pamiêci nie ma xD
		thr = nullptr;
	}
}

void IThread::Join()
{//co siê stanie jeœli pozamieniasz te kolejnoœci ustawienia statusu i danie join()?
	//jeœli nie uda siê zrobiæ joina to wtedy wywali nam b³ad i nie zmieni satusu na stopped, 
	//inaczej ni¿ w Stop()
	if (thr)
	{
		if (thr->joinable()) thr->join();
		status = IThread::Status::STOPPED;
		delete thr;
		thr = nullptr;
	}
}

bool IThread::isRunning() // sprawdzamy czy jest running, jeœli jest, to zwróci nam 1, jeœli nie, to 0
{//true albo false, a pod 1 jest te¿ zapisany running
	return status == IThread::Status::RUNNING;
}

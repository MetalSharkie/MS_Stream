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
	if (!thr)
	{
		status = IThread::Status::RUNNING;
		thr = new std::thread(&IThread::ThreadRoutine, this);
	}
}

void IThread::Stop()
{
	if (thr)
	{
		status = IThread::Status::STOPPED;
	 	if(thr->joinable()) thr->join();
		delete thr;
		thr = nullptr;
	}
}

void IThread::Join()
{
	if (thr)
	{
		if (thr->joinable()) thr->join();
		status = IThread::Status::STOPPED;
		delete thr;
		thr = nullptr;
	}
}

bool IThread::isRunning()
{
	return status == IThread::Status::RUNNING;
}

#pragma once
#include <thread>
class IThread
{
	enum Status
	{
		STOPPED,
		RUNNING
	};
	std::thread * thr;
	Status status;
public:
	IThread();
	virtual ~IThread();
	void Start();
	void Stop();
	void Join();
	bool isRunning();
	virtual void ThreadRoutine() = 0;
};


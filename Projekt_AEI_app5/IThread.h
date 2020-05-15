#pragma once
#include <thread>
class IThread
{
	enum Status
	{
		STOPPED,
		RUNNING
	};
	std::thread* thr; //wska�nik na obiekt w�tku
	Status status;
public:
	IThread();

	virtual ~IThread();
	void Start();
	void Stop();
	void Join();
	bool isRunning();

	virtual void ThreadRoutine() = 0; //ma opisywa� dzia�anie w�tku - obecnie ustawiona na 0!!!!
};


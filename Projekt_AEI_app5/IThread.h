#pragma once
#include <thread>
class IThread
{
	enum Status
	{
		STOPPED,
		RUNNING
	};
	std::thread* thr; //wska¿nik na obiekt w¹tku
	Status status;
public:
	IThread();

	virtual ~IThread();
	void Start();
	void Stop();
	void Join();
	bool isRunning();

	virtual void ThreadRoutine() = 0; //ma opisywaæ dzia³anie w¹tku - obecnie ustawiona na 0!!!!
};


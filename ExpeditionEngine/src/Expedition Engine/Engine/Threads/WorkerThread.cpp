#include "WorkerThread.h"

#include "../Tasks/EngineTask.h"


#include "ThreadManagerAttorney.h"

#include <functional>

void WorkerThread::Work()
{
	//First time creation
	{
		std::unique_lock<std::mutex> lock(workerMutex);
		conditionalVariable.wait(lock, [this] {return assignedTask; });
	}

	while (threadNeeded)
	{
		pCurrentTask->Execute();
		
		assignedTask = false;
		ThreadManagerAttorney::WorkerThreadControl::RecycleThread(this);

		std::unique_lock<std::mutex> lock(workerMutex);
		conditionalVariable.wait(lock, [this] {return assignedTask; });
	}
}

void WorkerThread::Initialize(EngineTask* pNextTask)
{
	pCurrentTask = pNextTask;
	assignedTask = true;
	std::lock_guard<std::mutex> lock(workerMutex);
	conditionalVariable.notify_one();
}

void WorkerThread::AssignTask(EngineTask* pNextTask)
{
	std::lock_guard<std::mutex> lock(workerMutex);
	pCurrentTask = pNextTask;
	assignedTask = true;
	conditionalVariable.notify_one();
}

void WorkerThread::ShutDownThread()
{
	{
		std::lock_guard<std::mutex> lock(workerMutex);
		threadNeeded = false;
		assignedTask = true;
		conditionalVariable.notify_one();
	}
	myThread.join();
}

WorkerThread::WorkerThread()
{
	myThread = std::thread(&WorkerThread::Work, this);
}

WorkerThread::~WorkerThread()
{
	
}
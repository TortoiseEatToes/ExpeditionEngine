#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include "WorkerThread.h"
#include "../Tasks/Task_Null.h"

#include "../../Containers/Containers.h"

#include <mutex>


class EngineTask;

//This class owns all of the WorkerThread objects and is used for our multithreading.
class ThreadManager
{
public:
	



private:
	friend class ThreadManagerAttorney;

	ThreadManager();
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager& operator= (const ThreadManager&) = delete;
	~ThreadManager();

	static ThreadManager& Instance()
	{
		return *pInstance;
	}

	static void Terminate()
	{
		delete pInstance;
	}

	static void Initialize()
	{
		pInstance = new ThreadManager();
	}

	static void InitializeThreads()
	{
		Instance().privInitializeThreads();
	}
	void privInitializeThreads();

	static ThreadManager* pInstance;

	//This will pop a workerThread from the pool and assign the given task to it.
	static void ExecuteTask(EngineTask* pTask)
	{
		Instance().privExecuteTask(pTask);
	}
	void privExecuteTask(EngineTask* pTask);

	//This is called by the workerThread objects so they can put themselves back into the pool.
	static void RecycleThread(WorkerThread* pWorkerThread)
	{
		Instance().privRecycleThread(pWorkerThread);
	}
	void privRecycleThread(WorkerThread* pWorkerThread);

	void WaitForAllWorkerThreadsToReturnToPool();
	
	Stack<WorkerThread*> availableWorkerThreads;
	Queue<EngineTask*> taskQueue;
	Task_Null nullTask;
	std::mutex managerMutex;
	WorkerThread* workerPool = nullptr;
	WorkerThread* pCurrentWorkerThread = nullptr;
	unsigned int numberOfWorkerThreads = -1;
};

#endif
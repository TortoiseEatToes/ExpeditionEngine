#include "ThreadManager.h"

ThreadManager* ThreadManager::pInstance = nullptr;

#include "../EngineUtilities.h"

#include <chrono>

void ThreadManager::privInitializeThreads()
{
	workerPool = new WorkerThread[numberOfWorkerThreads];

	for (unsigned int i = 0; i < numberOfWorkerThreads; ++i)
	{
		pCurrentWorkerThread = &workerPool[i];
		pCurrentWorkerThread->Initialize(&nullTask);
	}

	WaitForAllWorkerThreadsToReturnToPool();
}

ThreadManager::ThreadManager()
{
	numberOfWorkerThreads = std::thread::hardware_concurrency();
}

ThreadManager::~ThreadManager()
{
	WaitForAllWorkerThreadsToReturnToPool();

	while (availableWorkerThreads.GetSize() > 0)
	{
		pCurrentWorkerThread = availableWorkerThreads.Pop();
		pCurrentWorkerThread->ShutDownThread();
	}

	delete[] workerPool;
}

void ThreadManager::privExecuteTask(EngineTask* pTask)
{
	managerMutex.lock();

	if (availableWorkerThreads.GetSize() > 0)
	{
		pCurrentWorkerThread = availableWorkerThreads.Pop();
		pCurrentWorkerThread->AssignTask(pTask);
		EngineUtilities::PrintDebugLog("\nThreadManager: thread has been assigned a task");
	}
	else
	{
		taskQueue.Push(pTask);
		EngineUtilities::PrintDebugLog("\nThreadManager: THREAD NOT AVAILABLE, PUSHING TASK INTO QUEUE");
	}

	managerMutex.unlock();
}

void ThreadManager::privRecycleThread(WorkerThread* pWorkerThread)
{
	managerMutex.lock();

	if (taskQueue.GetSize() > 0)
	{
		pWorkerThread->AssignTask(taskQueue.Pop());
		EngineUtilities::PrintDebugLog("\nThreadManager: thread did NOT enter the pool, was assigned task instead");
	}
	else
	{
		availableWorkerThreads.Push(pWorkerThread);
		EngineUtilities::PrintDebugLog("\nThreadManager: thread has entered the pool");
	}

	managerMutex.unlock();
}

void ThreadManager::WaitForAllWorkerThreadsToReturnToPool()
{
	//Wait for all of the worker threads to return 
	while (availableWorkerThreads.GetSize() < static_cast<int>(numberOfWorkerThreads))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

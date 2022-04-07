#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>

class EngineTask;

//This object will execute it's assigned task and then put itself back into the ThreadManager's pool
class WorkerThread
{
private:
	std::condition_variable conditionalVariable;
	std::mutex workerMutex;
	EngineTask* pCurrentTask = nullptr;
	std::atomic_bool threadNeeded = true;
	bool assignedTask = false;

	std::thread myThread;

public:
	WorkerThread();
	WorkerThread(const WorkerThread&) = delete;
	WorkerThread& operator= (const WorkerThread&) = delete;
	~WorkerThread();

	/// <summary>This function is the work that the contained thread executes.</summary>
	void Work();
	
	/// <summary>The thread manager uses this function to ensure none of the threads try to access the ThreadManager too early.</summary>
	/// <param name="pNextTask">A pointer to the null task that is used to allow the thread to start it's while loop</param>
	void Initialize(EngineTask* pNextTask);

	/// <summary>This is used by the ThreadManager to wake the thread and get it working on this task.</summary>
	/// <param name="pNextTask">The task that needs to be executed by this worker</param>
	void AssignTask(EngineTask* pNextTask);

	/// <summary>This is used by the ThreadManager to shut down the thread inside of this class.</summary>
	void ShutDownThread();
};

#endif // !WORKERTHREAD_H
#pragma once

#include "ThreadManager.h"

class ThreadManagerAttorney
{
public:
	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void Initialize()
		{
			ThreadManager::Initialize();
		}

		static void InitializeThreads()
		{
			ThreadManager::InitializeThreads();
		}

		static void Terminate()
		{
			ThreadManager::Terminate();
		}
	};

	class EngineTaskControl
	{
	private:
		friend class EngineTask;

		static void ExecuteTask(EngineTask* pTask)
		{
			ThreadManager::ExecuteTask(pTask);
		}

	};

	class WorkerThreadControl
	{
	private:
		friend class WorkerThread;

		static void RecycleThread(WorkerThread* pWorkerThread)
		{
			ThreadManager::RecycleThread(pWorkerThread);
		}

	};
};
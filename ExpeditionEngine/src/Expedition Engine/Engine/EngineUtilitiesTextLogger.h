#pragma once

#include "EngineUtilitiesTextLoggerCommand.h"

#include "../Containers/Pool.h"
#include "../Containers/Queue.h"

#include <mutex>
#include <Windows.h>

class EngineUtilitiesTextLogger
{
public:
	EngineUtilitiesTextLogger() = default;
	EngineUtilitiesTextLogger(const EngineUtilitiesTextLogger&) = delete;
	EngineUtilitiesTextLogger& operator= (const EngineUtilitiesTextLogger&) = delete;
	~EngineUtilitiesTextLogger()
	{
		const EngineUtilitiesTextLoggerCommand* pTempCommand = nullptr;
		while (textOuputQueue.GetSize() > 0)
		{
			pTempCommand = textOuputQueue.Pop();
			textCommandPool.RecycleObject(pTempCommand);
		}

		while (textWarningQueue.GetSize() > 0)
		{
			pTempCommand = textWarningQueue.Pop();
			textCommandPool.RecycleObject(pTempCommand);
		}

		textCommandPool.DestroyAll();
	}

	void PushCommand(const std::string& output)
	{
		textCommandMutex.lock();

		ptempTextCommand = textCommandPool.GetPooledObject();
		ptempTextCommand->textToOutput = output;
		textOuputQueue.Push(ptempTextCommand);

		textCommandMutex.unlock();
	}

	void PushWarning(const std::string& output)
	{
		textCommandMutex.lock();

		ptempTextCommand = textCommandPool.GetPooledObject();
		ptempTextCommand->textToOutput = output;
		textWarningQueue.Push(ptempTextCommand);

		textCommandMutex.unlock();
	}

	void ExecuteDebugCommands()
	{
		textCommandMutex.lock();

		while (textOuputQueue.GetSize() > 0)
		{
			ptempTextCommand = textOuputQueue.Pop();
			Print(ptempTextCommand->textToOutput);
			textCommandPool.RecycleObject(ptempTextCommand);
		}

		textCommandMutex.unlock();
	}

	void PrintWarnings()
	{
		textCommandMutex.lock();

		if (textWarningQueue.GetSize() > 0)
		{
			Print("\n------------------ START WARNINGS --------------------\n");

			while (textWarningQueue.GetSize() > 0)
			{
				ptempTextCommand = textWarningQueue.Pop();
				Print(ptempTextCommand->textToOutput);
				textCommandPool.RecycleObject(ptempTextCommand);
			}

			Print("\n------------------ END WARNINGS --------------------\n");
		}

		textCommandMutex.unlock();
	}

private:
	void Print(const std::string& string)
	{
		OutputDebugStringA(string.c_str());
	}

	Queue<EngineUtilitiesTextLoggerCommand*> textOuputQueue;
	Queue<EngineUtilitiesTextLoggerCommand*> textWarningQueue;
	Pool<EngineUtilitiesTextLoggerCommand> textCommandPool;
	EngineUtilitiesTextLoggerCommand* ptempTextCommand;
	std::mutex textCommandMutex;
};
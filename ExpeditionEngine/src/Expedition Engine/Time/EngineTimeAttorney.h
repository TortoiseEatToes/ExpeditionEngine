#ifndef ENGINETIMEATTORNEY_H
#define ENGINETIMEATTORNEY_H

#include "EngineTime.h"

class EngineTimeAttorney
{
public:
	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void Initialize()
		{
			EngineTime::Initialize();
		}

		static void Terminate()
		{
			EngineTime::Terminate();
		}

		static void ProcessTime()
		{
			EngineTime::ProcessTime();
		}
	};

	class ResolveFrameControl
	{
	private:
		friend class Task_ResolveFrame;

		static void ProcessTime()
		{
			EngineTime::ProcessTime();
		}
	};
};

#endif // !ENGINETIMEATTORNEY_H
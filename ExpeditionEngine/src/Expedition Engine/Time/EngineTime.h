#ifndef ENGINETIME_H
#define ENGINETIME_H

#include "StopwatchFloat.h"

class EngineTime
{
public:

	/// <summary>Get the amount of time that has passed since the engine started.</summary>
	/// <returns>float copy of the amount of time that has passed since the engine started</returns> 
	float static GetCurrentEngineTime()
	{
		return Instance().privGetCurrentEngineTime();
	}

	/// <summary>Get the amount of time that has passed since the last frame.</summary>
	/// <returns>float copy of the delta time</returns> 
	float static GetDeltaTime()
	{
		return Instance().privGetDeltaTime();
	}


private:
	friend class EngineTimeAttorney;
	
	EngineTime();
	EngineTime(const EngineTime&) = delete;
	EngineTime& operator= (const EngineTime&) = delete;
	~EngineTime();
	
	static void ProcessTime()
	{
		Instance().privProcessTime();
	}

	static void Initialize()
	{
		pInstance = new EngineTime();
	}

	static EngineTime& Instance()
	{
		return *pInstance;
	}

	static void Terminate()
	{
		delete pInstance;
	}

	void privProcessTime();
	const float& privGetCurrentEngineTime();
	const float& privGetDeltaTime();

	static EngineTime* pInstance;

	StopwatchFloat stopwatch;
	float previousTime = 0.0f;
	float currentTime = 0.0f;
	float deltaTime = 0.0f;

};

#endif // !ENGINETIME_H

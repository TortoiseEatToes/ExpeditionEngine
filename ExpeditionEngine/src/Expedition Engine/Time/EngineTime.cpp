#include "EngineTime.h"

EngineTime* EngineTime::pInstance = nullptr;

EngineTime::EngineTime()
{
	stopwatch.Start();
}

EngineTime::~EngineTime()
{
}

void EngineTime::privProcessTime()
{
	deltaTime = stopwatch.Stop();

	previousTime = currentTime;

	currentTime = previousTime + deltaTime;

	stopwatch.Start();
}

const float& EngineTime::privGetCurrentEngineTime()
{
	return currentTime;
}

const float& EngineTime::privGetDeltaTime()
{
	return deltaTime;
}

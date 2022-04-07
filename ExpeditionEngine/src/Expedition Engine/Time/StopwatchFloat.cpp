#include "StopwatchFloat.h"


StopwatchFloat::StopwatchFloat()
{
	startTime = std::chrono::steady_clock::now();
	stopTime = std::chrono::steady_clock::now();
	elapsedTime = stopTime - startTime;
}

StopwatchFloat::StopwatchFloat(const StopwatchFloat& other)
{
	startTime = other.startTime;
	stopTime = other.stopTime;
	elapsedTime = other.elapsedTime;
}

StopwatchFloat& StopwatchFloat::operator=(const StopwatchFloat& other)
{
	if(&other != this)
	{
		startTime = other.startTime;
		stopTime = other.stopTime;
		elapsedTime = other.elapsedTime;
	}
	return *this;
}

void StopwatchFloat::Start()
{
	startTime = std::chrono::steady_clock::now();
}

float StopwatchFloat::Stop()
{
	stopTime = std::chrono::steady_clock::now();
	elapsedTime = stopTime - startTime;
	return elapsedTime.count();
}

float StopwatchFloat::Peak()
{
	elapsedTime = std::chrono::steady_clock::now() - startTime;
	return elapsedTime.count();
}

float StopwatchFloat::GetElapsedTime()
{
	return elapsedTime.count();
}

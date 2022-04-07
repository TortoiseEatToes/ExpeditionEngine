#ifndef STOPWATCHFLOAT_H
#define STOPWATCHFLOAT_H

#include <chrono>

class StopwatchFloat
{
public:
	StopwatchFloat();
	StopwatchFloat(const StopwatchFloat& other);
	StopwatchFloat& operator= (const StopwatchFloat& other);
	~StopwatchFloat() = default;

	/// <summary>Start tracking time.</summary>
	void Start();

	/// <summary>Stop tracking time.</summary>
	/// <returns>float elapsed time in seconds</returns>
	float Stop();

	/// <summary>Get the amount of time that has passed since the Stopwatch was started, but don't stop it.</summary>
	/// <returns>float elapsed time in seconds</returns>
	float Peak();

	/// <summary>Get the amount of time was stored that passed between the last start and stop.</summary>
	/// <returns>float elapsed time in seconds</returns>
	float GetElapsedTime();

private:
	std::chrono::time_point<std::chrono::steady_clock> startTime;
	std::chrono::time_point<std::chrono::steady_clock> stopTime;
	std::chrono::duration<float> elapsedTime;
};

#endif // !StopWatchFloat

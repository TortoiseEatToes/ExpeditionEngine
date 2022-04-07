#ifndef SCENETIMEMANAGER_H
#define SCENETIMEMANAGER_H

#include "StopwatchFloat.h"

class SceneTimeManager
{
public:
	SceneTimeManager();
	SceneTimeManager(const SceneTimeManager&) = delete;
	SceneTimeManager& operator= (const SceneTimeManager&) = delete;
	~SceneTimeManager();

	/// <summary>Get the amount of time that has progressed in this scene.</summary>
	/// <returns>const float reference to the currentTime</returns> 
	const float& GetCurrentSceneTime() const;

	/// <summary>Get the amount of time that has progressed since the last frame in this scene.</summary>
	/// <returns>const float reference to the deltaTime</returns> 
	const float& GetDeltaTime() const;

private:
	friend class SceneTimeManagerAttorney;

	void ProcessTime();
	void StartTime();
	void StopTime();

	StopwatchFloat stopwatch;
	float previousTime = 0.0f;
	float currentTime = 0.0f;
	float deltaTime = 0.0f;
};

#endif // !SCENETIMEMANAGER_H

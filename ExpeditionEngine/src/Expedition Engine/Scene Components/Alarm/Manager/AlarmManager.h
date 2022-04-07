#pragma once

#include "../AlarmComponentAttorney.h"

class AlarmComponent;
class SceneTimeManager;

class AlarmManager
{
public:
	AlarmManager() = delete;
	AlarmManager(SceneTimeManager& sceneTimeManager);
	AlarmManager(const AlarmManager& other) = delete;
	AlarmManager& operator= (const AlarmManager& other) = delete;
	~AlarmManager();

	/// <summary>This function is called by the scene that owns this manager.  It is used to check if any alarms have timed out.</summary>
	/// <param name="currentTime">The current time of this scene</param>
	void ProcessAlarms(const float& currentTime);

	void Register(AlarmComponent* pComponent, const float& timeUntilTrigger);
	void Deregister(AlarmComponent* pComponent);

private:
	PriorityQueueArray<AlarmComponent*, float> alarmQueue;
	SceneTimeManager* pSceneTimeManager;
	AlarmComponent* pTempAlarmComponent;
};
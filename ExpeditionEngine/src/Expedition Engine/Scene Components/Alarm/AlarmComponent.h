#pragma once

#include "../../Containers/PriorityQueueArray.h"
#include "../SceneComponent.h"

class AlarmComponent : public SceneComponent
{
public:
	AlarmComponent() = default;
	AlarmComponent(const AlarmComponent& other) = delete;
	AlarmComponent& operator= (const AlarmComponent& other) = delete;
	virtual ~AlarmComponent();


	/// <summary>Start this alarm.  After timeUntilTriggered seconds, OnAlarm will be called.</summary>
	/// <param name="sceneName">The SceneName that this object should register into</param>
	/// <param name="timeUntilTriggered">The SceneName that this object should register into</param> 
	void SetAlarm(const SceneName& sceneName, float timeUntilTriggered);

	/// <summary>Stop this alarm.  OnAlarm will no longer be called.</summary>
	void StopAlarm();


	/// <summary>Get the amount of time left until OnAlarm is triggered in seconds.</summary>
	/// <returns>A floating point value of the time left until the alarm is triggered in seconds.  Will return 0.0f if the alarm is not set.</returns> 
	float GetTimeRemaining() const;

protected:
	/// <summary>Override this function to define what should happen when this alarm is triggered.</summary>
	virtual void OnAlarm() = 0;

private:
	friend class AlarmComponentAttorney;

	void RegisterIntoSceneChild(EngineScene& engineScene) override;
	void DeregisterFromSceneChild(EngineScene& engineScene) override;

	void TriggerAlarm();

	enum RegisteredState
	{
		NotRegistered,
		Registered
	};

	PriorityQueueArray<AlarmComponent*, float>::Iterator& GetIterator();
	void SetEndPoint(const float& endPoint);
	//void SetIterator(std::multimap<float, AlarmComponent*>::iterator& otherIterator, const float& newEndPoint);

	PriorityQueueArray<AlarmComponent*, float>::Iterator iterator;
	float timeDuration;
	float timeEndPoint;
	RegisteredState currentRegisteredState = RegisteredState::NotRegistered;
};
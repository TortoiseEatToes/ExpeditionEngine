#include "AlarmComponent.h"

#include "../../Scenes/SceneManager.h"
#include "../../Scenes/EngineScene.h"

#include <assert.h>

void AlarmComponent::SetAlarm(const SceneName& sceneName, float timeUntilTriggered)
{
	assert(currentRegisteredState == RegisteredState::NotRegistered);
	currentRegisteredState = RegisteredState::Registered;
	registeredScene = sceneName;
	timeDuration = timeUntilTriggered;
	RegisterIntoScene();
}

void AlarmComponent::StopAlarm()
{
	if (currentRegisteredState == RegisteredState::Registered)
	{
		currentRegisteredState = RegisteredState::NotRegistered;
		DeregisterFromScene();
	}
}

float AlarmComponent::GetTimeRemaining() const
{
	if (currentRegisteredState == RegisteredState::Registered)
	{
		return timeEndPoint - SceneManager::GetScene(registeredScene)->GetTimeManager().GetCurrentSceneTime();
	}
	else
	{
		return 0.0f;
	}	
}

void AlarmComponent::RegisterIntoSceneChild(EngineScene& engineScene)
{
	engineScene.GetAlarmManager().Register(this, timeDuration);
}

void AlarmComponent::DeregisterFromSceneChild(EngineScene& engineScene)
{
	engineScene.GetAlarmManager().Deregister(this);
}

void AlarmComponent::TriggerAlarm()
{
	currentRegisteredState = RegisteredState::NotRegistered;
	OnAlarm();
}

PriorityQueueArray<AlarmComponent*, float>::Iterator& AlarmComponent::GetIterator()
{
	return iterator;
}

void AlarmComponent::SetEndPoint(const float & endPoint)
{
	timeEndPoint = endPoint;
}

//void AlarmComponent::SetIterator(std::multimap<float, AlarmComponent*>::iterator& otherIterator, const float& newEndPoint)
//{
//	iterator = otherIterator;
//	timeEndPoint = newEndPoint;
//}

AlarmComponent::~AlarmComponent()
{

}
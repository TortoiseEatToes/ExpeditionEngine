#include "AlarmManager.h"
#include "../../../Time/SceneTimeManager.h"
#include "../../../../Expedition Resources/AlarmSettings.h"

AlarmManager::AlarmManager(SceneTimeManager& sceneTimeManager)
	: alarmQueue(MaxNumberOfAlarmsPerScene)
{
	pSceneTimeManager = &sceneTimeManager;
}

AlarmManager::~AlarmManager()
{
}

void AlarmManager::ProcessAlarms(const float& currentTime)
{
	while (alarmQueue.Size() > 0 && currentTime > alarmQueue.PeekFrontPriority())
	{
		alarmQueue.Pop(pTempAlarmComponent);
		AlarmComponentAttorney::ManagerControl::TriggerAlarm(pTempAlarmComponent);
	}
}

void AlarmManager::Register(AlarmComponent* pComponent, const float& timeUntilTrigger)
{
	AlarmComponentAttorney::ManagerControl::SetEndPoint(pComponent, pSceneTimeManager->GetCurrentSceneTime() + timeUntilTrigger);
	alarmQueue.Push(pSceneTimeManager->GetCurrentSceneTime() + timeUntilTrigger, pComponent, AlarmComponentAttorney::ManagerControl::GetIterator(pComponent));
}

void AlarmManager::Deregister(AlarmComponent* pComponent)
{
	alarmQueue.Remove(AlarmComponentAttorney::ManagerControl::GetIterator(pComponent));
}

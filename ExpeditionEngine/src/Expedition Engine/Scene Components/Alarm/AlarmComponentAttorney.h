#pragma once

#include "AlarmComponent.h"

class AlarmComponentAttorney
{
public:
	struct ManagerControl
	{
	private:
		friend class AlarmManager;

		static void TriggerAlarm(AlarmComponent* pComponent)
		{
			pComponent->TriggerAlarm();
		}

		static PriorityQueueArray<AlarmComponent*, float>::Iterator& GetIterator(AlarmComponent* pComponent)
		{
			return pComponent->GetIterator();
		}

		static void SetEndPoint(AlarmComponent* pComponent, const float& endPoint)
		{
			pComponent->SetEndPoint(endPoint);
		}
	};
};
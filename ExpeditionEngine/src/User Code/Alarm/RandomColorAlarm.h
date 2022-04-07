#pragma once

#include "../../Expedition Engine/Game Object/Components/Alarm/AlarmComponent.h"

class GraphicsObject_Color;

class RandomColorAlarm : public AlarmComponent
{
public:
	GraphicsObject_Color* testInstance;
	int sideLen;
	float timeBetweenAlarms;

	RandomColorAlarm() = default;
	~RandomColorAlarm() = default;

private:
	void OnAlarm() override;
};
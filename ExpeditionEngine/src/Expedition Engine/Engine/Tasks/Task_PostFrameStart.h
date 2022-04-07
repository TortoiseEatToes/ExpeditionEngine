#pragma once

#include "EngineTask.h"

class Task_PostFrameStart : public EngineTask
{
public:
	Task_PostFrameStart();
	Task_PostFrameStart(const Task_PostFrameStart& other) = delete;
	Task_PostFrameStart& operator= (const Task_PostFrameStart& other) = delete;
	~Task_PostFrameStart() = default;

private:
	void Work() override;
};
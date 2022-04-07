#pragma once

#include "EngineTask.h"

class Task_MainLoopStart : public EngineTask
{
public:
	Task_MainLoopStart();
	Task_MainLoopStart(const Task_MainLoopStart& other) = delete;
	Task_MainLoopStart& operator= (const Task_MainLoopStart& other) = delete;
	~Task_MainLoopStart() = default;

private:
	void Work() override;
};
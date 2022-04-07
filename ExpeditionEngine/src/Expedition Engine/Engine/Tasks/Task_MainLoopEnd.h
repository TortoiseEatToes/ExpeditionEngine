#pragma once

#include "EngineTask.h"

class Task_MainLoopEnd : public EngineTask
{
public:
	Task_MainLoopEnd();
	Task_MainLoopEnd(const Task_MainLoopEnd& other) = delete;
	Task_MainLoopEnd& operator= (const Task_MainLoopEnd& other) = delete;
	~Task_MainLoopEnd() = default;

private:
	void Work() override;
};
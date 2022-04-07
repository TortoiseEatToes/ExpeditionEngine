#pragma once

#include "EngineTask.h"

class Task_PostFrameEnd : public EngineTask
{
public:
	Task_PostFrameEnd();
	Task_PostFrameEnd(const Task_PostFrameEnd& other) = delete;
	Task_PostFrameEnd& operator= (const Task_PostFrameEnd& other) = delete;
	~Task_PostFrameEnd() = default;

private:
	void Work() override;
};
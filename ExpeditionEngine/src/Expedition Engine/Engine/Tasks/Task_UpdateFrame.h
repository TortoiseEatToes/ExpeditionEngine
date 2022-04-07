#pragma once

#include "EngineTask.h"

class Task_UpdateFrame : public EngineTask
{
public:
	Task_UpdateFrame();
	Task_UpdateFrame(const Task_UpdateFrame& other) = delete;
	Task_UpdateFrame& operator= (const Task_UpdateFrame& other) = delete;
	~Task_UpdateFrame() = default;

private:
	void Work() override;
};
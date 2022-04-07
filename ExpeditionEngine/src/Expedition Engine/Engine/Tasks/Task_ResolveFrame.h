#pragma once

#include "EngineTask.h"

//This task processes time, commands, changes scenes, and calls the DX swap chain.
class Task_ResolveFrame : public EngineTask
{
public:
	Task_ResolveFrame();
	Task_ResolveFrame(const Task_ResolveFrame& other) = delete;
	Task_ResolveFrame& operator= (const Task_ResolveFrame& other) = delete;
	~Task_ResolveFrame() = default;

private:
	void Work() override;
};

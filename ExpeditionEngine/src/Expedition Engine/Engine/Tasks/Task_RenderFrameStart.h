#pragma once

#include "EngineTask.h"

class Task_RenderFrameStart : public EngineTask
{
public:
	Task_RenderFrameStart();
	Task_RenderFrameStart(const Task_RenderFrameStart& other) = delete;
	Task_RenderFrameStart& operator= (const Task_RenderFrameStart& other) = delete;
	~Task_RenderFrameStart() = default;

private:
	void Work() override;
};
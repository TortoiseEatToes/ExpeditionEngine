#pragma once

#include "EngineTask.h"

class Task_RenderFrameEnd : public EngineTask
{
public:
	Task_RenderFrameEnd();
	Task_RenderFrameEnd(const Task_RenderFrameEnd& other) = delete;
	Task_RenderFrameEnd& operator= (const Task_RenderFrameEnd& other) = delete;
	~Task_RenderFrameEnd() = default;

private:
	void Work() override;
};
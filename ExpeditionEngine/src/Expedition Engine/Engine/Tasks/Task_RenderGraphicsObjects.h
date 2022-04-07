#pragma once

#include "EngineTask.h"

//This task is used for executing all of the major graphics related work.
class Task_RenderGraphicsObjects : public EngineTask
{
public:
	Task_RenderGraphicsObjects();
	Task_RenderGraphicsObjects(const Task_RenderGraphicsObjects& other) = delete;
	Task_RenderGraphicsObjects& operator= (const Task_RenderGraphicsObjects& other) = delete;
	~Task_RenderGraphicsObjects() = default;

private:
	void Work() override;
};
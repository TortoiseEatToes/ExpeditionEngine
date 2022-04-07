#pragma once

#include "EngineTask.h"

//This task is used for executing all of the major graphics related work.
class Task_RenderParticles : public EngineTask
{
public:
	Task_RenderParticles();
	Task_RenderParticles(const Task_RenderParticles& other) = delete;
	Task_RenderParticles& operator= (const Task_RenderParticles& other) = delete;
	~Task_RenderParticles() = default;

private:
	void Work() override;
};
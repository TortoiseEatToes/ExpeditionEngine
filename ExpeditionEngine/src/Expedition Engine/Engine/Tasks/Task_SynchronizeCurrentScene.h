#pragma once
#include "EngineTask.h"

//This task is in charge of making sure that all of the double buffers are synchronized and ready for the next frame.
class Task_SynchronizeCurrentScene : public EngineTask
{
public:
	Task_SynchronizeCurrentScene();
	Task_SynchronizeCurrentScene(const Task_SynchronizeCurrentScene& other) = delete;
	Task_SynchronizeCurrentScene& operator= (const Task_SynchronizeCurrentScene& other) = delete;
	~Task_SynchronizeCurrentScene() = default;

private:
	void Work() override;
};
#pragma once


#include "EngineTask.h"

//This task is in charge of making sure that all of the double buffers are synchronized and ready for the next frame.
class Task_SynchronizeCurrentGraphicsScene : public EngineTask
{
public:
	Task_SynchronizeCurrentGraphicsScene();
	Task_SynchronizeCurrentGraphicsScene(const Task_SynchronizeCurrentGraphicsScene& other) = delete;
	Task_SynchronizeCurrentGraphicsScene& operator= (const Task_SynchronizeCurrentGraphicsScene& other) = delete;
	~Task_SynchronizeCurrentGraphicsScene() = default;

private:
	void Work() override;
};
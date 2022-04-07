#include "Task_SynchronizeCurrentGraphicsScene.h"

#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"

Task_SynchronizeCurrentGraphicsScene::Task_SynchronizeCurrentGraphicsScene()
	: EngineTask("Synchronize Current Graphics Scene", EngineTask::PriorityLevel::High)
{
}

void Task_SynchronizeCurrentGraphicsScene::Work()
{
	GraphicsSceneManagerAttorney::SynchronizeControl::Synchronize();
}

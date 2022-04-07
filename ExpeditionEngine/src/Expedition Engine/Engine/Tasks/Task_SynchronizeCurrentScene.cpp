#include "Task_SynchronizeCurrentScene.h"

#include "../../Scenes/SceneManagerAttorney.h"

Task_SynchronizeCurrentScene::Task_SynchronizeCurrentScene()
	: EngineTask("Synchronize Current Scene", EngineTask::PriorityLevel::High)
{
}

void Task_SynchronizeCurrentScene::Work()
{
	SceneManagerAttorney::SynchronizeSceneControl::SynchronizeCurrentScene();
}

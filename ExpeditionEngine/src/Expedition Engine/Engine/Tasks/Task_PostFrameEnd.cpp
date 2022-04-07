#include "Task_PostFrameEnd.h"

#include "../../Scenes/SceneManagerAttorney.h"

Task_PostFrameEnd::Task_PostFrameEnd()
	: EngineTask("PostFrameEnd", EngineTask::PriorityLevel::High)
{
	//Do nothing
}

void Task_PostFrameEnd::Work()
{
	SceneManagerAttorney::PostFrameEndControl::ProcessSceneChangeCommands();
}
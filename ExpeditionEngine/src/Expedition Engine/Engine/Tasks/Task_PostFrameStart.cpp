#include "Task_PostFrameStart.h"

#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"

Task_PostFrameStart::Task_PostFrameStart()
	: EngineTask("PostFrameStart", EngineTask::PriorityLevel::High)
{
	//Do nothing
}

void Task_PostFrameStart::Work()
{
	GraphicsSceneManagerAttorney::ResolveFrameControl::ProcessCurrentSceneCommands();
}
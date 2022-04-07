#include "Task_MainLoopEnd.h"

#include "../ExpeditionEngineAttorney.h"

Task_MainLoopEnd::Task_MainLoopEnd()
	: EngineTask("MainLoopEnd", EngineTask::PriorityLevel::High)
{
	//Do nothing
}

void Task_MainLoopEnd::Work()
{
	ExpeditionEngineAttorney::MainLoopEndControl::WakeMainThread();
}
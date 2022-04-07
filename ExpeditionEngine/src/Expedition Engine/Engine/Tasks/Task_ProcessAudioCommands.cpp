#include "Task_ProcessAudioCommands.h"

#include "../../Audio/AudioSystemAttorney.h"

Task_ProcessAudioCommands::Task_ProcessAudioCommands()
	: EngineTask("ProcessAudioCommands", EngineTask::PriorityLevel::High)
{
}

void Task_ProcessAudioCommands::Work()
{
	AudioSystemAttorney::TaskControl::ProcessAudioCommands();
}

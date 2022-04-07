#include "Task_ResolveFrame.h"

#include "../../Time/EngineTimeAttorney.h"
#include "../ExpeditionEngineAttorney.h"
#include "../../Scenes/SceneManagerAttorney.h"
#include "../../DX12App/DXApp/DXApp_12.h"

Task_ResolveFrame::Task_ResolveFrame()
	: EngineTask("Resolve Frame", EngineTask::PriorityLevel::High)
{
	//Do nothing
}

void Task_ResolveFrame::Work()
{
	EngineTimeAttorney::ResolveFrameControl::ProcessTime();

	//ExpeditionEngineAttorney::ResolveFrameControl::ProcessMessages();
	ExpeditionEngineAttorney::ResolveFrameControl::ExecuteCommandQueue();

	SceneManagerAttorney::ResolveFrameControl::ProccessSceneCreationAndDeletionCommands();

	DXApp_12::PrepareToRender();
}
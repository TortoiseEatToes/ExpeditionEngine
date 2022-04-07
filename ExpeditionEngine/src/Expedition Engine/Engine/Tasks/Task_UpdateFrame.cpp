#include "Task_UpdateFrame.h"


#include "../../Scenes/SceneManagerAttorney.h"
#include "../../DX12App/DXApp/DXApp_12.h"


Task_UpdateFrame::Task_UpdateFrame()
	: EngineTask("Update Frame", EngineTask::PriorityLevel::High)
{
}

void Task_UpdateFrame::Work()
{
	SceneManagerAttorney::UpdateFrameControl::ExecuteUpdateStep();
	//DXApp_12::Update();
}

#include "Task_RenderFrameEnd.h"

#include "../../DX12App/DXApp/DXApp_12.h"

Task_RenderFrameEnd::Task_RenderFrameEnd()
	: EngineTask("RenderFrameEnd", EngineTask::PriorityLevel::High)
{
	//Do nothing
}

void Task_RenderFrameEnd::Work()
{
	DXApp_12::FinishRendering();
}

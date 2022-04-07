#include "Task_RenderGraphicsObjects.h"

#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"
#include "../../UI/UIManagerAttorney.h"
#include "../../DX12App/DXApp/DXApp_12.h"
#include "../../../Expedition Resources/EngineSettings.h"

Task_RenderGraphicsObjects::Task_RenderGraphicsObjects()
	: EngineTask("Render Graphics Objects", EngineTask::PriorityLevel::High)
{
	//Do nothing
}

void Task_RenderGraphicsObjects::Work()
{
	GraphicsSceneManagerAttorney::RenderControl::RenderFrame();
}
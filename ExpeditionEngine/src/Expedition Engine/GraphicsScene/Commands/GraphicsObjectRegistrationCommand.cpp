#include "GraphicsObjectRegistrationCommand.h"
#include "../GraphicsSceneManagerAttorney.h"

void GraphicsObjectRegistrationCommand::Execute(GraphicsScene* pGraphicsScene)
{
	pAction->Execute(pGraphicsScene, pGraphicsObject);
}

void GraphicsObjectRegistrationCommand::RecycleCommand()
{
	GraphicsSceneManagerAttorney::CommandCalls::RecycleCommand(this);
}

void GraphicsObjectRegistrationCommand::Initialize(GraphicsObjectRegistrationActionStrategy* pNewAction, GraphicsObject* pGO) {
	pAction = pNewAction;
	pGraphicsObject = pGO;
}
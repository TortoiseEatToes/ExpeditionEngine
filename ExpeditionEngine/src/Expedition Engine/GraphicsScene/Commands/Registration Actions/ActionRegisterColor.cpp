#include "ActionRegisterColor.h"
#include "../../GraphicsSceneAttorney.h"

void ActionRegisterColor::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) 
{
	GraphicsSceneAttorney::ActionControls::RegisterGraphicsObjectColor(pGraphicsObject, pGraphicsScene);
}
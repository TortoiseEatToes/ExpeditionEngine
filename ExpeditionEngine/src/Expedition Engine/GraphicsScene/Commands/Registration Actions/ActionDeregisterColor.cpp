#include "ActionDeregisterColor.h"
#include "../../GraphicsSceneAttorney.h"

void ActionDeregisterColor::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) 
{
	GraphicsSceneAttorney::ActionControls::DeregisterGraphicsObjectColor(pGraphicsObject, pGraphicsScene);
}
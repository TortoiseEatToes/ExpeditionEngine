#include "ActionDeregisterColorLight.h"
#include "../../GraphicsSceneAttorney.h"

void ActionDeregisterColorLight::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) 
{
	GraphicsSceneAttorney::ActionControls::DeregisterGraphicsObjectColorLight(pGraphicsObject, pGraphicsScene);
}
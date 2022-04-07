#include "ActionDeregisterTextureLight.h"
#include "../../GraphicsSceneAttorney.h"

void ActionDeregisterTextureLight::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) 
{
	GraphicsSceneAttorney::ActionControls::DeregisterGraphicsObjectTextureLight(pGraphicsObject, pGraphicsScene);
}

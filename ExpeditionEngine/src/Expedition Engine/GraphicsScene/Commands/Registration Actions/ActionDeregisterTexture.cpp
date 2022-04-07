#include "ActionDeregisterTexture.h"
#include "../../GraphicsSceneAttorney.h"

void ActionDeregisterTexture::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) 
{
	GraphicsSceneAttorney::ActionControls::DeregisterGraphicsObjectTexture(pGraphicsObject, pGraphicsScene);
}

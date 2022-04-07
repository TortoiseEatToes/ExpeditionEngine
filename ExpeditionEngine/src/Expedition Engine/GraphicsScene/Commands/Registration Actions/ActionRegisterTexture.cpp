#include "ActionRegisterTexture.h"
#include "../../GraphicsSceneAttorney.h"

void ActionRegisterTexture::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject)
{
	GraphicsSceneAttorney::ActionControls::RegisterGraphicsObjectTexture(pGraphicsObject, pGraphicsScene);
}

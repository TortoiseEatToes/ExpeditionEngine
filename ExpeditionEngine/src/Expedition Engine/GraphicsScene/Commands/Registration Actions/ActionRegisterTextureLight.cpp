#include "ActionRegisterTextureLight.h"
#include "../../GraphicsSceneAttorney.h"

void ActionRegisterTextureLight::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject)
{
	GraphicsSceneAttorney::ActionControls::RegisterGraphicsObjectTextureLight(pGraphicsObject, pGraphicsScene);
}

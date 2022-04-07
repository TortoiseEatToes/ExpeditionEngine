#include "ActionRegisterColorLight.h"
#include "../../GraphicsSceneAttorney.h"

void ActionRegisterColorLight::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject)
{
	GraphicsSceneAttorney::ActionControls::RegisterGraphicsObjectColorLight(pGraphicsObject, pGraphicsScene);
}

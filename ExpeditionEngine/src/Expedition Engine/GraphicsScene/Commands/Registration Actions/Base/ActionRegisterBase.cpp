#include "ActionRegisterBase.h"
#include "../../../GraphicsSceneAttorney.h"



void ActionRegisterBase::Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) {
	GraphicsSceneAttorney::ActionControls::RegisterGraphicsObject(pGraphicsObject, pGraphicsScene);
}

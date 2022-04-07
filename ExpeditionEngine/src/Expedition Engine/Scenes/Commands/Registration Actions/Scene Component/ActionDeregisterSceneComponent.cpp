#include "ActionDeregisterSceneComponent.h"

#include "../../../../Scene Components/SceneComponentAttorney.h"

void ActionDeregisterSceneComponent::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	SceneComponentAttorney::CommandControl::DeregisterFromScene(pComponent.Scene, engineScene);
}

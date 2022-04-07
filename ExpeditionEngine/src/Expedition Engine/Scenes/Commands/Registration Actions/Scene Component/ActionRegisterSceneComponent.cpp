#include "ActionRegisterSceneComponent.h"
#include "../../../../Scene Components/SceneComponentAttorney.h"

void ActionRegisterSceneComponent::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	SceneComponentAttorney::CommandControl::RegisterIntoScene(pComponent.Scene, engineScene);
}

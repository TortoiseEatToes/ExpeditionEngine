#include "SceneComponent.h"

#include "../Scenes/SceneManagerAttorney.h"


const SceneName& SceneComponent::GetRegisteredScene()
{
	return registeredScene;
}

void SceneComponent::RegisterIntoScene()
{
	SceneManagerAttorney::SceneComponentControl::RegisterComponent(this, registeredScene);
}

void SceneComponent::DeregisterFromScene()
{
	SceneManagerAttorney::SceneComponentControl::DeregisterComponent(this, registeredScene);
}

void SceneComponent::cmdRegisterIntoScene(EngineScene& engineScene)
{
	RegisterIntoSceneChild(engineScene);
}

void SceneComponent::cmdDeregisterFromScene(EngineScene& engineScene)
{
	DeregisterFromSceneChild(engineScene);
}

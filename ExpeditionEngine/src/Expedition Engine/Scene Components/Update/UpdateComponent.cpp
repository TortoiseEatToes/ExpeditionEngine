#include "UpdateComponent.h"
#include "../../Scenes/EngineScene.h"

UpdateComponent::UpdateComponent()
{

}

void UpdateComponent::StartUpdating(const SceneName& sceneToRegisterInto)
{
	registeredScene = sceneToRegisterInto;
	RegisterIntoScene();
}

void UpdateComponent::StopUpdating()
{
	DeregisterFromScene();
}

void UpdateComponent::RegisterIntoSceneChild(EngineScene& engineScene)
{
	engineScene.GetUpdateManager().Register(this);
}

void UpdateComponent::DeregisterFromSceneChild(EngineScene& engineScene)
{
	engineScene.GetUpdateManager().Deregister(this);
}

UpdateComponent::~UpdateComponent()
{

}
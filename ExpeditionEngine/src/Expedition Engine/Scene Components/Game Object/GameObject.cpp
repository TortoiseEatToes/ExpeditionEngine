#include "GameObject.h"

#include "../../Scenes/EngineScene.h"


GameObject::GameObject(const SceneName& startingScene)
{
	registeredScene = startingScene;
}

void GameObject::EnterScene(const SceneName& sceneName)
{
	registeredScene = sceneName;
	SceneComponent::RegisterIntoScene();
}

void GameObject::ExitScene()
{
	DeregisterFromScene();
}

void GameObject::RegisterIntoSceneChild(EngineScene& engineScene)
{
	engineScene.GetGameObjectManager().Register(this);
}

void GameObject::DeregisterFromSceneChild(EngineScene& engineScene)
{
	engineScene.GetGameObjectManager().Deregister(this);
}

List<GameObject*>::Iterator& GameObject::GetIterator()
{
	return iterator;
}

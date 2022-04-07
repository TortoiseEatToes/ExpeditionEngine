#include "GameObjectManager.h"


GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Register(GameObject* pGameObject)
{
	liveGameObjects.PushFront(pGameObject, GameObjectAttorney::ManagerControl::GetIterator(pGameObject));
	GameObjectAttorney::ManagerControl::ExecuteOnSceneEnter(pGameObject);
}

void GameObjectManager::Deregister(GameObject* pGameObject)
{
	liveGameObjects.Remove(GameObjectAttorney::ManagerControl::GetIterator(pGameObject));
	GameObjectAttorney::ManagerControl::ExecuteOnSceneExit(pGameObject);
}

void GameObjectManager::ForceAllGameObjectsToExitScene()
{
	liveGameObjects.SetFront(gameObjectIterator);
	while (!gameObjectIterator.IsOutOfNodes())
	{
		gameObjectIterator.GetCurrentObject()->ExitScene();
		++gameObjectIterator;
	}
}

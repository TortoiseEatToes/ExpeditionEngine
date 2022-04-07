#pragma once

#include "../GameObjectAttorney.h"

class GameObjectManager
{
public:
	GameObjectManager();
	GameObjectManager(const GameObjectManager& other) = delete;
	GameObjectManager& operator= (const GameObjectManager& other) = delete;
	~GameObjectManager();

	void Register(GameObject* pGameObject);
	void Deregister(GameObject* pGameObject);

	void ForceAllGameObjectsToExitScene();

private:
	List<GameObject*> liveGameObjects;
	List<GameObject*>::Iterator gameObjectIterator;
};
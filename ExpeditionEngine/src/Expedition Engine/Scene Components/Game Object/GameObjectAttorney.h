#pragma once
#include "GameObject.h"

class GameObjectAttorney
{
public:
	struct ManagerControl
	{
	private:
		friend class GameObjectManager;

		static void ExecuteOnSceneEnter(GameObject* pGameObject)
		{
			pGameObject->OnSceneEnter();
		}

		static void ExecuteOnSceneExit(GameObject* pGameObject)
		{
			pGameObject->OnSceneExit();
		}

		static List<GameObject*>::Iterator& GetIterator(GameObject* pGameObject)
		{
			return pGameObject->GetIterator();
		}
	};
};
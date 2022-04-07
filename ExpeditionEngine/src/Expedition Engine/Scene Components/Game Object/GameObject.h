#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../SceneComponent.h"

#include "../../Containers/List.h"

class GameObject : public SceneComponent
{
public:
	GameObject() = delete;
	GameObject(const SceneName& startingScene);
	GameObject(const GameObject& other) = delete;
	GameObject& operator= (const GameObject& other) = delete;
	virtual ~GameObject() = default;

	/// <summary>Register this game object into the scene given in the parameter.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	void EnterScene(const SceneName& sceneName);

	/// <summary>Deregister this game object from the scene.</summary>
	void ExitScene();


protected:
	/// <summary>Override this to define what should happen when this game object enters a scene</summary>
	virtual void OnSceneEnter() = 0;

	/// <summary>Override this to define what should happen when this game object exits a scene</summary>
	virtual void OnSceneExit() = 0;

private:
	friend class GameObjectAttorney;

	void RegisterIntoSceneChild(EngineScene& engineScene) override;
	void DeregisterFromSceneChild(EngineScene& engineScene) override;

	List<GameObject*>::Iterator& GetIterator();
	List<GameObject*>::Iterator iterator;
};

#endif // !GAMEOBJECT_H

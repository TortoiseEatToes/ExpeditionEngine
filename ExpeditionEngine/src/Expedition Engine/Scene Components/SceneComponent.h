#pragma once

#include "../../Expedition Resources/SceneSettings.h"

class EngineScene;

class SceneComponent
{
public:
	SceneComponent() = default;
	SceneComponent(const SceneComponent& other) = delete;
	SceneComponent& operator= (const SceneComponent& other) = delete;
	virtual ~SceneComponent() = default;

	/// <summary>Return the scene that this component is registered into.</summary>
	/// <returns>A const reference to the SceneName object on this component</returns> 
	const SceneName& GetRegisteredScene();

protected:
	/// <summary>The child class calls this function to register into a scene</summary>
	void RegisterIntoScene();

	/// <summary>The child class calls this function to deregister from the scene</summary>
	void DeregisterFromScene();

	/// <summary>The user child implements this function to define what it means to register into a scene</summary>
	virtual void RegisterIntoSceneChild(EngineScene& engineScene) = 0;
	/// <summary>The user child implements this function to define what it means to deregister from a scene</summary>
	virtual void DeregisterFromSceneChild(EngineScene& engineScene) = 0;

	SceneName registeredScene;

private:
	friend class SceneComponentAttorney;
	//The registration command calls this
	void cmdRegisterIntoScene(EngineScene& engineScene);

	void cmdDeregisterFromScene(EngineScene& engineScene);
};

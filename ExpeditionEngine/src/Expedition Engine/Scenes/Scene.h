#pragma once

#include "../../Expedition Resources/SceneSettings.h"

class SceneTimeManager;
class Camera;
class EngineScene;

class Scene
{
public:
	Scene() = delete;
	Scene(const SceneName& startingSceneName);
	Scene(const Scene& other) = delete;
	Scene& operator= (const Scene& other) = delete;
	virtual ~Scene() = default;

	/// <summary>If you need more information about the current time, delta time, etc.  Use this function to get the time manager.</summary>
	/// <returns>Return a const reference to the time manager.</returns> 
	const SceneTimeManager& GetTimeManager() const;

	void SetCurrentPerspectiveCamera(Camera* const pCamera);
	void SetCurrentOrthographicCamera(Camera* const pCamera);

	Camera* const GetCurrentPerspectiveCamera();
	Camera* const GetCurrentOrthographicCamera();

protected:

	/// <summary>Override this to define what should happen when the scene is first created.</summary>
	virtual void SceneInitialize() {};

	/// <summary>Override this to define what should happen when this scene becomes the current scene.</summary>
	virtual void SceneStart() {};

	/// <summary>Override this to define what should happen when this scene is no longer the current scene.</summary>
	virtual void SceneStop() {};

	/// <summary>Override this to define what should happen when this scene is about to be destroyed.</summary>
	virtual void SceneShutDown() {};

	SceneName sceneName;

private:
	friend class SceneAttorney;

	void EngineIntitialization(EngineScene * const pInitEngineScene);

	EngineScene* pEngineScene;
};
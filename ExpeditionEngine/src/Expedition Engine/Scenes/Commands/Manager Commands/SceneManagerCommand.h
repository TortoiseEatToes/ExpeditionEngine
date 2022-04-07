#pragma once
#include "../../../../Expedition Resources/SceneSettings.h"

class Scene;

class SceneManagerCommand
{
public:
	SceneManagerCommand() = default;
	SceneManagerCommand(const SceneManagerCommand& other) = delete;
	SceneManagerCommand& operator= (const SceneManagerCommand& other) = delete;
	virtual ~SceneManagerCommand() = default;

	void Initialize(const SceneName& newSceneToAffect)
	{
		sceneName = newSceneToAffect;
	}
	virtual void Execute() = 0;

protected:
	SceneName sceneName;
};
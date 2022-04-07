#pragma once

#include "SceneManagerCommand.h"

template<typename T>
class SceneCreationCommand : public SceneManagerCommand
{
public:
	SceneCreationCommand() = default;
	SceneCreationCommand(const SceneCreationCommand& other) = delete;
	SceneCreationCommand& operator= (const SceneCreationCommand& other) = delete;
	virtual ~SceneCreationCommand() = default;

	
	void Execute() override
	{
		SceneManager::cmdCreateScene<T>(sceneName);
	}

private:
};
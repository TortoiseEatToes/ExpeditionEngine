#pragma once

class Scene;

class SceneCommand
{
public:
	SceneCommand() = default;
	SceneCommand(const SceneCommand& other) = delete;
	SceneCommand& operator= (const SceneCommand& other) = delete;
	virtual ~SceneCommand() = default;


	virtual void Execute(EngineScene* const pEngineScene) = 0;
	virtual void RecycleCommand() = 0;
};
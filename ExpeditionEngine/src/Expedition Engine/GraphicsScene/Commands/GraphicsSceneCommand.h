#pragma once

class GraphicsScene;

class GraphicsSceneCommand
{
public:
	GraphicsSceneCommand() = default;
	GraphicsSceneCommand(const GraphicsSceneCommand& other) = delete;
	GraphicsSceneCommand& operator= (const GraphicsSceneCommand& other) = delete;
	~GraphicsSceneCommand() = default;


	virtual void Execute(GraphicsScene* pScene) = 0;
	virtual void RecycleCommand() = 0;
};
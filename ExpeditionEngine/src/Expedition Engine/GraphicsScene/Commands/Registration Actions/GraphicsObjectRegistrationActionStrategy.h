#pragma once

class GraphicsScene;

class GraphicsObject;

class GraphicsObjectRegistrationActionStrategy
{
public:
	GraphicsObjectRegistrationActionStrategy() = default;
	GraphicsObjectRegistrationActionStrategy(const GraphicsObjectRegistrationActionStrategy& other) = delete;
	GraphicsObjectRegistrationActionStrategy& operator= (const GraphicsObjectRegistrationActionStrategy& other) = delete;
	virtual ~GraphicsObjectRegistrationActionStrategy() = default;

	//Use the same bytes regardless of what component you want
	virtual void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) = 0;
};
#pragma once

#include "GraphicsSceneCommand.h"
#include "Registration Actions/GraphicsObjectRegistrationActionStrategy.h"

class GraphicObject;

class GraphicsObjectRegistrationCommand : public GraphicsSceneCommand
{
public:
	GraphicsObjectRegistrationCommand() = default;
	GraphicsObjectRegistrationCommand(const GraphicsObjectRegistrationCommand& other) = delete;
	GraphicsObjectRegistrationCommand& operator= (const GraphicsObjectRegistrationCommand& other) = delete;
	~GraphicsObjectRegistrationCommand() = default;

	void Initialize(GraphicsObjectRegistrationActionStrategy* pNewAction, GraphicsObject* pGO);

	void Execute(GraphicsScene* pGraphicsScene) override;

	void RecycleCommand() override;

private:
	GraphicsObjectRegistrationActionStrategy* pAction;
	GraphicsObject* pGraphicsObject;
};
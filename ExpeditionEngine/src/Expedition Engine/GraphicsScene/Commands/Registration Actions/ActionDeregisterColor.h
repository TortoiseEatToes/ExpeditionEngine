#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionDeregisterColor : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionDeregisterColor() = default;
	ActionDeregisterColor(ActionDeregisterColor&& other) = delete;
	ActionDeregisterColor(const ActionDeregisterColor& other) = delete;
	ActionDeregisterColor& operator= (ActionDeregisterColor&& other) = delete;
	ActionDeregisterColor& operator= (const ActionDeregisterColor& other) = delete;
	~ActionDeregisterColor() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

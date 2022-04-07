#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionRegisterColor : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionRegisterColor() = default;
	ActionRegisterColor(ActionRegisterColor&& other) = delete;
	ActionRegisterColor(const ActionRegisterColor& other) = delete;
	ActionRegisterColor& operator= (ActionRegisterColor&& other) = delete;
	ActionRegisterColor& operator= (const ActionRegisterColor& other) = delete;
	~ActionRegisterColor() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionDeregisterColorLight : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionDeregisterColorLight() = default;
	ActionDeregisterColorLight(ActionDeregisterColorLight&& other) = delete;
	ActionDeregisterColorLight(const ActionDeregisterColorLight& other) = delete;
	ActionDeregisterColorLight& operator= (ActionDeregisterColorLight&& other) = delete;
	ActionDeregisterColorLight& operator= (const ActionDeregisterColorLight& other) = delete;
	~ActionDeregisterColorLight() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

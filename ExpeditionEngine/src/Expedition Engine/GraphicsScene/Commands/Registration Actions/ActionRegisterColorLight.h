#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionRegisterColorLight : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionRegisterColorLight() = default;
	ActionRegisterColorLight(ActionRegisterColorLight&& other) = delete;
	ActionRegisterColorLight(const ActionRegisterColorLight& other) = delete;
	ActionRegisterColorLight& operator= (ActionRegisterColorLight&& other) = delete;
	ActionRegisterColorLight& operator= (const ActionRegisterColorLight& other) = delete;
	~ActionRegisterColorLight() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

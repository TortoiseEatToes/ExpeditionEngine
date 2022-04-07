#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputMouseKeyOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputMouseKeyOnPressed() = default;
	ActionDeregisterInputMouseKeyOnPressed(const ActionDeregisterInputMouseKeyOnPressed& other) = delete;
	ActionDeregisterInputMouseKeyOnPressed& operator= (const ActionDeregisterInputMouseKeyOnPressed& other) = delete;
	~ActionDeregisterInputMouseKeyOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputMouseKeyOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputMouseKeyOnHeld() = default;
	ActionDeregisterInputMouseKeyOnHeld(const ActionDeregisterInputMouseKeyOnHeld& other) = delete;
	ActionDeregisterInputMouseKeyOnHeld& operator= (const ActionDeregisterInputMouseKeyOnHeld& other) = delete;
	~ActionDeregisterInputMouseKeyOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
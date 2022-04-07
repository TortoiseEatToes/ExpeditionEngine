#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputMouseActionOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputMouseActionOnHeld() = default;
	ActionDeregisterInputMouseActionOnHeld(const ActionDeregisterInputMouseActionOnHeld& other) = delete;
	ActionDeregisterInputMouseActionOnHeld& operator= (const ActionDeregisterInputMouseActionOnHeld& other) = delete;
	~ActionDeregisterInputMouseActionOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
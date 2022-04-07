#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputKeyboardActionOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputKeyboardActionOnHeld() = default;
	ActionDeregisterInputKeyboardActionOnHeld(const ActionDeregisterInputKeyboardActionOnHeld& other) = delete;
	ActionDeregisterInputKeyboardActionOnHeld& operator= (const ActionDeregisterInputKeyboardActionOnHeld& other) = delete;
	~ActionDeregisterInputKeyboardActionOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
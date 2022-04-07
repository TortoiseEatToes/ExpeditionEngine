#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputKeyboardKeyOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputKeyboardKeyOnHeld() = default;
	ActionDeregisterInputKeyboardKeyOnHeld(const ActionDeregisterInputKeyboardKeyOnHeld& other) = delete;
	ActionDeregisterInputKeyboardKeyOnHeld& operator= (const ActionDeregisterInputKeyboardKeyOnHeld& other) = delete;
	~ActionDeregisterInputKeyboardKeyOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};

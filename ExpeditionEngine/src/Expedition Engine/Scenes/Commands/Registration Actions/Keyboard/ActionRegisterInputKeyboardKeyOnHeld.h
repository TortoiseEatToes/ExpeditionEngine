#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputKeyboardKeyOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputKeyboardKeyOnHeld() = default;
	ActionRegisterInputKeyboardKeyOnHeld(const ActionRegisterInputKeyboardKeyOnHeld& other) = delete;
	ActionRegisterInputKeyboardKeyOnHeld& operator= (const ActionRegisterInputKeyboardKeyOnHeld& other) = delete;
	~ActionRegisterInputKeyboardKeyOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputKeyboardActionOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputKeyboardActionOnHeld() = default;
	ActionRegisterInputKeyboardActionOnHeld(const ActionRegisterInputKeyboardActionOnHeld& other) = delete;
	ActionRegisterInputKeyboardActionOnHeld& operator= (const ActionRegisterInputKeyboardActionOnHeld& other) = delete;
	~ActionRegisterInputKeyboardActionOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
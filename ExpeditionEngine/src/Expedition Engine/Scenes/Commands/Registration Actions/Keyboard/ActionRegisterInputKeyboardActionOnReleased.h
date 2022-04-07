#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputKeyboardActionOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputKeyboardActionOnReleased() = default;
	ActionRegisterInputKeyboardActionOnReleased(const ActionRegisterInputKeyboardActionOnReleased& other) = delete;
	ActionRegisterInputKeyboardActionOnReleased& operator= (const ActionRegisterInputKeyboardActionOnReleased& other) = delete;
	~ActionRegisterInputKeyboardActionOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
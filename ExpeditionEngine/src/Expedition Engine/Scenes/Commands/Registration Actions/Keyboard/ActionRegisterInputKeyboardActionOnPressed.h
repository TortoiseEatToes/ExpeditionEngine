#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputKeyboardActionOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputKeyboardActionOnPressed() = default;
	ActionRegisterInputKeyboardActionOnPressed(const ActionRegisterInputKeyboardActionOnPressed& other) = delete;
	ActionRegisterInputKeyboardActionOnPressed& operator= (const ActionRegisterInputKeyboardActionOnPressed& other) = delete;
	~ActionRegisterInputKeyboardActionOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
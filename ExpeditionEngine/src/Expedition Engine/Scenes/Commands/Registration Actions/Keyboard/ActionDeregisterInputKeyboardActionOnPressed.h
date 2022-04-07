#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputKeyboardActionOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputKeyboardActionOnPressed() = default;
	ActionDeregisterInputKeyboardActionOnPressed(const ActionDeregisterInputKeyboardActionOnPressed& other) = delete;
	ActionDeregisterInputKeyboardActionOnPressed& operator= (const ActionDeregisterInputKeyboardActionOnPressed& other) = delete;
	~ActionDeregisterInputKeyboardActionOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
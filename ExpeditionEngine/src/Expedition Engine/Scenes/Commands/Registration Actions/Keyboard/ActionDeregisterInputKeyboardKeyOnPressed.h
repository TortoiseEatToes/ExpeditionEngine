#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputKeyboardKeyOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputKeyboardKeyOnPressed() = default;
	ActionDeregisterInputKeyboardKeyOnPressed(const ActionDeregisterInputKeyboardKeyOnPressed& other) = delete;
	ActionDeregisterInputKeyboardKeyOnPressed& operator= (const ActionDeregisterInputKeyboardKeyOnPressed& other) = delete;
	~ActionDeregisterInputKeyboardKeyOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
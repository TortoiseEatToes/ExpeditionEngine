#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputKeyboardActionOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputKeyboardActionOnReleased() = default;
	ActionDeregisterInputKeyboardActionOnReleased(const ActionDeregisterInputKeyboardActionOnReleased& other) = delete;
	ActionDeregisterInputKeyboardActionOnReleased& operator= (const ActionDeregisterInputKeyboardActionOnReleased& other) = delete;
	~ActionDeregisterInputKeyboardActionOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};

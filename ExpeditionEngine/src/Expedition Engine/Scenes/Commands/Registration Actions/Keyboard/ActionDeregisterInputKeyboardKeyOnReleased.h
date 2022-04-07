#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputKeyboardKeyOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputKeyboardKeyOnReleased() = default;
	ActionDeregisterInputKeyboardKeyOnReleased(const ActionDeregisterInputKeyboardKeyOnReleased& other) = delete;
	ActionDeregisterInputKeyboardKeyOnReleased& operator= (const ActionDeregisterInputKeyboardKeyOnReleased& other) = delete;
	~ActionDeregisterInputKeyboardKeyOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
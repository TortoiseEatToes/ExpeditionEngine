#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputKeyboardKeyOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputKeyboardKeyOnReleased() = default;
	ActionRegisterInputKeyboardKeyOnReleased(const ActionRegisterInputKeyboardKeyOnReleased& other) = delete;
	ActionRegisterInputKeyboardKeyOnReleased& operator= (const ActionRegisterInputKeyboardKeyOnReleased& other) = delete;
	~ActionRegisterInputKeyboardKeyOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
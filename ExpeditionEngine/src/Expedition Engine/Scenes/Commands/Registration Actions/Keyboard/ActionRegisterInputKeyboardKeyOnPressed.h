#pragma once


#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputKeyboardKeyOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputKeyboardKeyOnPressed() = default;
	ActionRegisterInputKeyboardKeyOnPressed(const ActionRegisterInputKeyboardKeyOnPressed& other) = delete;
	ActionRegisterInputKeyboardKeyOnPressed& operator= (const ActionRegisterInputKeyboardKeyOnPressed& other) = delete;
	~ActionRegisterInputKeyboardKeyOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
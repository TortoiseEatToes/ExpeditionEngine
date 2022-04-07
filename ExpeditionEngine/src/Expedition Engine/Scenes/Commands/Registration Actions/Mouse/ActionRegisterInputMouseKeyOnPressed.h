#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputMouseKeyOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputMouseKeyOnPressed() = default;
	ActionRegisterInputMouseKeyOnPressed(const ActionRegisterInputMouseKeyOnPressed& other) = delete;
	ActionRegisterInputMouseKeyOnPressed& operator= (const ActionRegisterInputMouseKeyOnPressed& other) = delete;
	~ActionRegisterInputMouseKeyOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
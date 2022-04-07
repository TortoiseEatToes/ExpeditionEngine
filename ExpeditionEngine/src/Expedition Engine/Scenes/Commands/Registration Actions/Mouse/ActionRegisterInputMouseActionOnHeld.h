#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputMouseActionOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputMouseActionOnHeld() = default;
	ActionRegisterInputMouseActionOnHeld(const ActionRegisterInputMouseActionOnHeld& other) = delete;
	ActionRegisterInputMouseActionOnHeld& operator= (const ActionRegisterInputMouseActionOnHeld& other) = delete;
	~ActionRegisterInputMouseActionOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
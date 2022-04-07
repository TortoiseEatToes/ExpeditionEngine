#pragma once


#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputMouseKeyOnHeld : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputMouseKeyOnHeld() = default;
	ActionRegisterInputMouseKeyOnHeld(const ActionRegisterInputMouseKeyOnHeld& other) = delete;
	ActionRegisterInputMouseKeyOnHeld& operator= (const ActionRegisterInputMouseKeyOnHeld& other) = delete;
	~ActionRegisterInputMouseKeyOnHeld() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
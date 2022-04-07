#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputMouseKeyOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputMouseKeyOnReleased() = default;
	ActionRegisterInputMouseKeyOnReleased(const ActionRegisterInputMouseKeyOnReleased& other) = delete;
	ActionRegisterInputMouseKeyOnReleased& operator= (const ActionRegisterInputMouseKeyOnReleased& other) = delete;
	~ActionRegisterInputMouseKeyOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
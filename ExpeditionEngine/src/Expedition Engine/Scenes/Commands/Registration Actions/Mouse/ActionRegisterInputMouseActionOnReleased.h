#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputMouseActionOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputMouseActionOnReleased() = default;
	ActionRegisterInputMouseActionOnReleased(const ActionRegisterInputMouseActionOnReleased& other) = delete;
	ActionRegisterInputMouseActionOnReleased& operator= (const ActionRegisterInputMouseActionOnReleased& other) = delete;
	~ActionRegisterInputMouseActionOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
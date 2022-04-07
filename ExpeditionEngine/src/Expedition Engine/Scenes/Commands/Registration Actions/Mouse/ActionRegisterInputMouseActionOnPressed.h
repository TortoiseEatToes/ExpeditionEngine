#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterInputMouseActionOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterInputMouseActionOnPressed() = default;
	ActionRegisterInputMouseActionOnPressed(const ActionRegisterInputMouseActionOnPressed& other) = delete;
	ActionRegisterInputMouseActionOnPressed& operator= (const ActionRegisterInputMouseActionOnPressed& other) = delete;
	~ActionRegisterInputMouseActionOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
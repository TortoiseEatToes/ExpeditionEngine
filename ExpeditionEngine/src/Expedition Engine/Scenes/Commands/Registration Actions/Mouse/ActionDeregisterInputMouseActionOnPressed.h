#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputMouseActionOnPressed : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputMouseActionOnPressed() = default;
	ActionDeregisterInputMouseActionOnPressed(const ActionDeregisterInputMouseActionOnPressed& other) = delete;
	ActionDeregisterInputMouseActionOnPressed& operator= (const ActionDeregisterInputMouseActionOnPressed& other) = delete;
	~ActionDeregisterInputMouseActionOnPressed() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
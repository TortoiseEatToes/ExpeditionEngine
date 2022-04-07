#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputMouseActionOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputMouseActionOnReleased() = default;
	ActionDeregisterInputMouseActionOnReleased(const ActionDeregisterInputMouseActionOnReleased& other) = delete;
	ActionDeregisterInputMouseActionOnReleased& operator= (const ActionDeregisterInputMouseActionOnReleased& other) = delete;
	~ActionDeregisterInputMouseActionOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
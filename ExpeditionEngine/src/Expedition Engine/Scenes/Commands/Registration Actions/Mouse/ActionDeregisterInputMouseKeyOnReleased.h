#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterInputMouseKeyOnReleased : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterInputMouseKeyOnReleased() = default;
	ActionDeregisterInputMouseKeyOnReleased(const ActionDeregisterInputMouseKeyOnReleased& other) = delete;
	ActionDeregisterInputMouseKeyOnReleased& operator= (const ActionDeregisterInputMouseKeyOnReleased& other) = delete;
	~ActionDeregisterInputMouseKeyOnReleased() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
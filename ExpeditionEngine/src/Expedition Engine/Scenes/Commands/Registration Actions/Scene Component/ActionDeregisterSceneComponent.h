#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionDeregisterSceneComponent : public ComponentRegistrationActionStrategy
{
public:
	ActionDeregisterSceneComponent() = default;
	ActionDeregisterSceneComponent(const ActionDeregisterSceneComponent& other) = delete;
	ActionDeregisterSceneComponent& operator= (const ActionDeregisterSceneComponent& other) = delete;
	~ActionDeregisterSceneComponent() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
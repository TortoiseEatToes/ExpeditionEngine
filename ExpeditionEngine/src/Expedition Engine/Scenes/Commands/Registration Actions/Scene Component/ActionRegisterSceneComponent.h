#pragma once

#include "../ComponentRegistrationActionStrategy.h"

class Scene;

class ActionRegisterSceneComponent : public ComponentRegistrationActionStrategy
{
public:
	ActionRegisterSceneComponent() = default;
	ActionRegisterSceneComponent(const ActionRegisterSceneComponent& other) = delete;
	ActionRegisterSceneComponent& operator= (const ActionRegisterSceneComponent& other) = delete;
	~ActionRegisterSceneComponent() = default;

	void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) override;
};
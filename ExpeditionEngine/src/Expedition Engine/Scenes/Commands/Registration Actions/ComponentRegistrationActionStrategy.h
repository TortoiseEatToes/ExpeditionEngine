#pragma once

class EngineScene;

class GameObject;
class UpdateComponent;
class AlarmComponent;
class KeyboardInputComponent;
class MouseInputComponent;
class SceneComponent;

class ComponentRegistrationActionStrategy
{
public:
	ComponentRegistrationActionStrategy() = default;
	ComponentRegistrationActionStrategy(const ComponentRegistrationActionStrategy& other) = delete;
	ComponentRegistrationActionStrategy& operator= (const ComponentRegistrationActionStrategy& other) = delete;
	virtual ~ComponentRegistrationActionStrategy() = default;

	union Component
	{
		GameObject* GameObject;
		UpdateComponent* Update;
		AlarmComponent* Alarm;
		KeyboardInputComponent* KeyboardInput;
		MouseInputComponent* MouseInput;
		SceneComponent* Scene;
	};

	union Atribute
	{
		float time;
		int index;
	};

	//Use the same bytes regardless of what component you want
	virtual void Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute) = 0;
};
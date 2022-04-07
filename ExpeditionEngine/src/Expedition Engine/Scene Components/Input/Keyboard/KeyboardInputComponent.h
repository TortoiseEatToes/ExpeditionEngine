#pragma once

#include "../../../Containers/List.h"

#include "../Input.h"

#include "../../SceneComponent.h"

class KeyboardInputComponent : public SceneComponent
{
public:
	KeyboardInputComponent();
	KeyboardInputComponent(const KeyboardInputComponent& other) = delete;
	KeyboardInputComponent& operator= (const KeyboardInputComponent& other) = delete;
	virtual ~KeyboardInputComponent();

	//--------------------------------------- Input Mouse -----------------------------------------
	/// <summary>Register the OnPressed, OnHeld, and OnReleased events to the same input.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="input">The Keyboard input type to register into</param>
	void RegisterForAll(const SceneName& sceneName, const Input::Keyboard input);

	/// <summary>Register the OnPressed event to an input</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="input">The Keyboard input type to register into</param>
	void RegisterForOnPressed(const SceneName& sceneName, const Input::Keyboard input);

	/// <summary>Register the OnHeld event to an input</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="input">The Keyboard input type to register into</param>
	void RegisterForOnHeld(const SceneName& sceneName, const Input::Keyboard input);

	/// <summary>Register the OnReleased event to an input</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="input">The Keyboard input type to register into</param>
	void RegisterForOnReleased(const SceneName& sceneName, const Input::Keyboard input);

	//--------------------------------------- Input Actions --------------------------------------------
	/// <summary>Register into OnPressed, OnHeld, and OnReleased events.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The InputAction to register into</param>
	void RegisterForAll(const SceneName& sceneName, const InputActions action);

	/// <summary>Register the OnPressed event to an InputAction.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The InputAction to register into</param>
	void RegisterForOnPressed(const SceneName& sceneName, const InputActions action);

	/// <summary>Register the OnHeld event to an InputAction.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The InputAction to register into</param>
	void RegisterForOnHeld(const SceneName& sceneName, const InputActions action);

	/// <summary>Register the OnReleased event to an InputAction.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The InputAction to register into</param>
	void RegisterForOnReleased(const SceneName& sceneName, const InputActions action);

	// ---------------------------------- Deregister -----------------------------------------
	/// <summary>Deregister the OnPressed, OnHeld, and OnReleased events</summary>
	void DeregisterFromAll();

	/// <summary>Deregister the OnPressed event</summary>
	void DeregisterFromOnPressed();

	/// <summary>Deregister the OnHeld event</summary>
	void DeregisterFromOnHeld();

	/// <summary>Deregister OnReleased event</summary>
	void DeregisterFromOnReleased();

protected:
	/// <summary>Override this to define what should happen when the registered key is pressed down.</summary>
	virtual void OnKeyPressed() {};

	/// <summary>Override this to define what should happen when the registered key is held down.</summary>
	virtual void OnKeyHeld() {};

	/// <summary>Override this to define what should happen when the registered key is released.</summary>
	virtual void OnKeyReleased() {};

private:
	friend class KeyboardInputComponentAttorney;

	void RegisterIntoSceneChild(EngineScene& engineScene) override;
	void DeregisterFromSceneChild(EngineScene& engineScene) override;

	enum TrackingState
	{
		NotRegistered,
		RegisteredAction,
		RegisteredInput
	};

	void privRegisterForOnPressed(const Input::Keyboard& input);
	void privRegisterForOnHeld(const Input::Keyboard& input);
	void privRegisterForOnReleased(const Input::Keyboard& input);

	void privRegisterForOnPressed(const InputActions& action);
	void privRegisterForOnHeld(const InputActions& action);
	void privRegisterForOnReleased(const InputActions& action);

	List<KeyboardInputComponent*>::Iterator& GetIteratorOnPressed();
	List<KeyboardInputComponent*>::Iterator& GetIteratorOnHeld();
	List<KeyboardInputComponent*>::Iterator& GetIteratorOnReleased();
	
	List<KeyboardInputComponent*>::Iterator iteratorOnPressed;
	List<KeyboardInputComponent*>::Iterator iteratorOnHeld;
	List<KeyboardInputComponent*>::Iterator iteratorOnReleased;

	TrackingState onPressedState = TrackingState::NotRegistered;
	TrackingState onHeldState = TrackingState::NotRegistered;
	TrackingState onReleasedState = TrackingState::NotRegistered;

	int enumIdOnPressed = -1;
	int enumIdOnHeld = -1;
	int enumIdOnReleased = -1;
};
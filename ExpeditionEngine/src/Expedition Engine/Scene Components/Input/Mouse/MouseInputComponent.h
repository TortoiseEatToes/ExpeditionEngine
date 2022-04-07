#pragma once

#include "../../../Containers/List.h"
#include "../Input.h"
#include "../../SceneComponent.h"

class MouseInputComponent : public SceneComponent
{
public:
	MouseInputComponent();
	MouseInputComponent(const MouseInputComponent& other) = delete;
	MouseInputComponent& operator= (const MouseInputComponent& other) = delete;
	virtual ~MouseInputComponent();

	//--------------------------------------- Input Mouse -----------------------------------------
	/// <summary>Register the OnPressed, OnHeld, and OnReleased events to the same input.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="input">The Mouse input type to register into</param>
	void RegisterForAll(const SceneName& sceneName, const Input::Mouse input);

	/// <summary>Register the OnPressed event to an input</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The Mouse input type to register into</param>
	void RegisterForOnPressed(const SceneName& sceneName, const Input::Mouse input);

	/// <summary>Register the OnHeld event to an input</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The Mouse input type to register into</param>
	void RegisterForOnHeld(const SceneName& sceneName, const Input::Mouse input);
	
	/// <summary>Register the OnReleased event to an input</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The Mouse input type to register into</param>
	void RegisterForOnReleased(const SceneName& sceneName, const Input::Mouse input);

	//--------------------------------------- Input Actions --------------------------------------------
	/// <summary>Register into OnPressed, OnHeld, and OnReleased events.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The InputAction to register into</param>
	void RegisterForAll(const SceneName& sceneName, const InputActions action);

	/// <summary>Register into the OnPressed event.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The InputAction to register into</param>
	void RegisterForOnPressed(const SceneName& sceneName, const InputActions action);

	/// <summary>Register into the OnHeld event.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	/// <param name="sceneToRegisterInto">The InputAction to register into</param>
	void RegisterForOnHeld(const SceneName& sceneName, const InputActions action);

	/// <summary>Register into the OnReleased event.</summary>
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

	/// <summary>Deregister the OnReleased event</summary>
	void DeregisterFromOnReleased();

	// ---------------------------------- Getters ---------------------------------------------------
	/// <summary>Get the X component of the Mouse position in pixels</summary>
	/// <returns>Integer for the X value of the mouse's position</returns> 
	const int& GetMousePositionX();

	/// <summary>Get the Y component of the Mouse position in pixels</summary>
	/// <returns>Integer for the Y value of the mouse's position</returns> 
	const int& GetMousePositionY();

protected:

	/// <summary>Override this to define what should happen when the registered key is pressed down.</summary>
	virtual void OnPressed() {};

	/// <summary>Override this to define what should happen when the registered key is held down.</summary>
	virtual void OnHeld() {};

	/// <summary>Override this to define what should happen when the registered key is released.</summary>
	virtual void OnReleased() {};

private:
	friend class MouseInputComponentAttorney;

	enum TrackingState
	{
		NotRegistered,
		RegisteredAction,
		RegisteredInput
	};

	void RegisterIntoSceneChild(EngineScene& engineScene) override;
	void DeregisterFromSceneChild(EngineScene& engineScene) override;

	void privRegisterForOnPressed(const Input::Mouse& input);
	void privRegisterForOnHeld(const Input::Mouse& input);
	void privRegisterForOnReleased(const Input::Mouse& input);

	void privRegisterForOnPressed(const InputActions& action);
	void privRegisterForOnHeld(const InputActions& action);
	void privRegisterForOnReleased(const InputActions& action);

	List<MouseInputComponent*>::Iterator& GetIteratorOnPressed();
	List<MouseInputComponent*>::Iterator& GetIteratorOnHeld();
	List<MouseInputComponent*>::Iterator& GetIteratorOnReleased();
	
	List<MouseInputComponent*>::Iterator iteratorOnPressed;
	List<MouseInputComponent*>::Iterator iteratorOnHeld;
	List<MouseInputComponent*>::Iterator iteratorOnReleased;

	TrackingState onPressedState = TrackingState::NotRegistered;
	TrackingState onHeldState = TrackingState::NotRegistered;
	TrackingState onReleasedState = TrackingState::NotRegistered;

	int enumIdOnPressed = -1;
	int enumIdOnHeld = -1;
	int enumIdOnReleased = -1;
};
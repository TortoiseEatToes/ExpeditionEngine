#include "KeyboardInputComponent.h"

#include "../../../Scenes/SceneManagerAttorney.h"

KeyboardInputComponent::KeyboardInputComponent()
{
}

void KeyboardInputComponent::RegisterForAll(const SceneName& sceneName, const Input::Keyboard input)
{
	registeredScene = sceneName;
	privRegisterForOnPressed(input);
	privRegisterForOnHeld(input);
	privRegisterForOnReleased(input);
}

void KeyboardInputComponent::RegisterForOnPressed(const SceneName& sceneName, const Input::Keyboard input)
{
	registeredScene = sceneName;
	privRegisterForOnPressed(input);
}

void KeyboardInputComponent::RegisterForOnHeld(const SceneName& sceneName, const Input::Keyboard input)
{
	registeredScene = sceneName;
	privRegisterForOnHeld(input);
}

void KeyboardInputComponent::RegisterForOnReleased(const SceneName& sceneName, const Input::Keyboard input)
{
	registeredScene = sceneName;
	privRegisterForOnReleased(input);
}

void KeyboardInputComponent::RegisterForAll(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnPressed(action);
	privRegisterForOnHeld(action);
	privRegisterForOnReleased(action);
}

void KeyboardInputComponent::RegisterForOnPressed(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnPressed(action);
}

void KeyboardInputComponent::RegisterForOnHeld(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnHeld(action);
}

void KeyboardInputComponent::RegisterForOnReleased(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnReleased(action);
}

void KeyboardInputComponent::DeregisterFromAll()
{
	DeregisterFromOnPressed();
	DeregisterFromOnHeld();
	DeregisterFromOnReleased();
}

void KeyboardInputComponent::DeregisterFromOnPressed()
{
	assert(onPressedState != TrackingState::NotRegistered);
	if (onPressedState == TrackingState::RegisteredAction)
	{
		SceneManagerAttorney::KeyboardInputControl::DeregisterComponentInputOnPressedAction(this, enumIdOnPressed);
		onPressedState = TrackingState::NotRegistered;
	}
	else //if(onPressedState == TrackingState::RegisteredInput)
	{
		SceneManagerAttorney::KeyboardInputControl::DeregisterComponentInputOnPressedInput(this, enumIdOnPressed);
		onPressedState = TrackingState::NotRegistered;
	}
}

void KeyboardInputComponent::DeregisterFromOnHeld()
{
	assert(onHeldState != TrackingState::NotRegistered);
	if (onHeldState == TrackingState::RegisteredAction)
	{
		SceneManagerAttorney::KeyboardInputControl::DeregisterComponentInputOnHeldAction(this, enumIdOnHeld);
		onHeldState = TrackingState::NotRegistered;
	}
	else //if(onHeldState == TrackingState::RegisteredInput)
	{
		SceneManagerAttorney::KeyboardInputControl::DeregisterComponentInputOnHeldInput(this, enumIdOnHeld);
		onHeldState = TrackingState::NotRegistered;
	}
}

void KeyboardInputComponent::DeregisterFromOnReleased()
{
	assert(onReleasedState != TrackingState::NotRegistered);
	if (onReleasedState == TrackingState::RegisteredAction)
	{
		SceneManagerAttorney::KeyboardInputControl::DeregisterComponentInputOnReleasedAction(this, enumIdOnReleased);
		onReleasedState = TrackingState::NotRegistered;
	}
	else //if(onReleasedState == TrackingState::RegisteredInput)
	{
		SceneManagerAttorney::KeyboardInputControl::DeregisterComponentInputOnReleasedInput(this, enumIdOnReleased);
		onReleasedState = TrackingState::NotRegistered;
	}
}

void KeyboardInputComponent::RegisterIntoSceneChild(EngineScene& engineScene)
{
}

void KeyboardInputComponent::DeregisterFromSceneChild(EngineScene& engineScene)
{
}

void KeyboardInputComponent::privRegisterForOnPressed(const Input::Keyboard& input)
{
	assert(onPressedState == TrackingState::NotRegistered);
	SceneManagerAttorney::KeyboardInputControl::RegisterComponentInputOnPressed(this, input);
	onPressedState = TrackingState::RegisteredInput;
	enumIdOnPressed = input;
}

void KeyboardInputComponent::privRegisterForOnHeld(const Input::Keyboard& input)
{
	assert(onHeldState == TrackingState::NotRegistered);
	SceneManagerAttorney::KeyboardInputControl::RegisterComponentInputOnHeld(this, input);
	onHeldState = TrackingState::RegisteredInput;
	enumIdOnHeld = input;
}

void KeyboardInputComponent::privRegisterForOnReleased(const Input::Keyboard& input)
{
	assert(onReleasedState == TrackingState::NotRegistered);
	SceneManagerAttorney::KeyboardInputControl::RegisterComponentInputOnReleased(this, input);
	onReleasedState = TrackingState::RegisteredInput;
	enumIdOnReleased = input;
}

void KeyboardInputComponent::privRegisterForOnPressed(const InputActions& action)
{
	assert(onPressedState == TrackingState::NotRegistered);
	SceneManagerAttorney::KeyboardInputControl::RegisterComponentInputOnPressed(this, action);
	onPressedState = TrackingState::RegisteredAction;
	enumIdOnPressed = action;
}

void KeyboardInputComponent::privRegisterForOnHeld(const InputActions& action)
{
	assert(onHeldState == TrackingState::NotRegistered);
	SceneManagerAttorney::KeyboardInputControl::RegisterComponentInputOnHeld(this, action);
	onHeldState = TrackingState::RegisteredAction;
	enumIdOnHeld = action;
}

void KeyboardInputComponent::privRegisterForOnReleased(const InputActions& action)
{
	assert(onReleasedState == TrackingState::NotRegistered);
	SceneManagerAttorney::KeyboardInputControl::RegisterComponentInputOnReleased(this, action);
	onReleasedState = TrackingState::RegisteredAction;
	enumIdOnReleased = action;
}

List<KeyboardInputComponent*>::Iterator& KeyboardInputComponent::GetIteratorOnPressed()
{
	return iteratorOnPressed;
}

List<KeyboardInputComponent*>::Iterator& KeyboardInputComponent::GetIteratorOnHeld()
{
	return iteratorOnHeld;
}

List<KeyboardInputComponent*>::Iterator& KeyboardInputComponent::GetIteratorOnReleased()
{
	return iteratorOnReleased;
}

KeyboardInputComponent::~KeyboardInputComponent()
{

}
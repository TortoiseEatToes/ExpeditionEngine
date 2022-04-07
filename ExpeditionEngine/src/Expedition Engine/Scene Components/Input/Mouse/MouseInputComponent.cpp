#include "MouseInputComponent.h"

#include "../../../Scenes/SceneManagerAttorney.h"

MouseInputComponent::MouseInputComponent()
{

}

void MouseInputComponent::RegisterForAll(const SceneName& sceneName, const Input::Mouse input)
{	
	registeredScene = sceneName;
	privRegisterForOnPressed(input);
	privRegisterForOnHeld(input);
	privRegisterForOnReleased(input);
}

void MouseInputComponent::RegisterForOnPressed(const SceneName& sceneName, const Input::Mouse input)
{
	registeredScene = sceneName;
	privRegisterForOnPressed(input);
}

void MouseInputComponent::RegisterForOnHeld(const SceneName& sceneName, const Input::Mouse input)
{
	registeredScene = sceneName;
	privRegisterForOnHeld(input);
}

void MouseInputComponent::RegisterForOnReleased(const SceneName& sceneName, const Input::Mouse input)
{
	registeredScene = sceneName;
	privRegisterForOnReleased(input);
}

void MouseInputComponent::RegisterForAll(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnPressed(action);
	privRegisterForOnHeld(action);
	privRegisterForOnReleased(action);
}

void MouseInputComponent::RegisterForOnPressed(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnPressed(action);
}

void MouseInputComponent::RegisterForOnHeld(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnHeld(action);
}

void MouseInputComponent::RegisterForOnReleased(const SceneName& sceneName, const InputActions action)
{
	registeredScene = sceneName;
	privRegisterForOnReleased(action);
}

void MouseInputComponent::DeregisterFromAll()
{
	DeregisterFromOnPressed();
	DeregisterFromOnHeld();
	DeregisterFromOnReleased();
}

void MouseInputComponent::DeregisterFromOnPressed()
{
	assert(onPressedState != TrackingState::NotRegistered);
	if (onPressedState == TrackingState::RegisteredAction)
	{
		SceneManagerAttorney::MouseInputControl::DeregisterComponentInputOnPressedAction(this, enumIdOnPressed);
		onPressedState = TrackingState::NotRegistered;
	}
	else //if(onPressedState == TrackingState::RegisteredInput)
	{
		SceneManagerAttorney::MouseInputControl::DeregisterComponentInputOnPressedInput(this, enumIdOnPressed);
		onPressedState = TrackingState::NotRegistered;
	}
}

void MouseInputComponent::DeregisterFromOnHeld()
{
	assert(onHeldState != TrackingState::NotRegistered);
	if (onHeldState == TrackingState::RegisteredAction)
	{
		SceneManagerAttorney::MouseInputControl::DeregisterComponentInputOnHeldAction(this, enumIdOnHeld);
		onHeldState = TrackingState::NotRegistered;
	}
	else //if (onHeldState == TrackingState::RegisteredInput)
	{
		SceneManagerAttorney::MouseInputControl::DeregisterComponentInputOnHeldInput(this, enumIdOnHeld);
		onHeldState = TrackingState::NotRegistered;
	}
}

void MouseInputComponent::DeregisterFromOnReleased()
{
	assert(onReleasedState != TrackingState::NotRegistered);
	if (onReleasedState == TrackingState::RegisteredAction)
	{
		SceneManagerAttorney::MouseInputControl::DeregisterComponentInputOnReleasedAction(this, enumIdOnReleased);
		onReleasedState = TrackingState::NotRegistered;
	}
	else //if (onReleasedState == TrackingState::RegisteredInput)
	{
		SceneManagerAttorney::MouseInputControl::DeregisterComponentInputOnReleasedInput(this, enumIdOnReleased);
		onReleasedState = TrackingState::NotRegistered;
	}
}

const int& MouseInputComponent::GetMousePositionX()
{
	return InputManager::GetMouseXPosition();
}

const int& MouseInputComponent::GetMousePositionY()
{
	return InputManager::GetMouseYPosition();
}

List<MouseInputComponent*>::Iterator& MouseInputComponent::GetIteratorOnPressed()
{
	return iteratorOnPressed;
}

List<MouseInputComponent*>::Iterator& MouseInputComponent::GetIteratorOnHeld()
{
	return iteratorOnHeld;
}

List<MouseInputComponent*>::Iterator& MouseInputComponent::GetIteratorOnReleased()
{
	return iteratorOnReleased;
}

MouseInputComponent::~MouseInputComponent()
{
}

void MouseInputComponent::RegisterIntoSceneChild(EngineScene& engineScene)
{
}

void MouseInputComponent::DeregisterFromSceneChild(EngineScene& engineScene)
{
}

void MouseInputComponent::privRegisterForOnPressed(const Input::Mouse& input)
{
	assert(onPressedState == TrackingState::NotRegistered);
	SceneManagerAttorney::MouseInputControl::RegisterComponentInputOnPressed(this, input);
	onPressedState = TrackingState::RegisteredInput;
	enumIdOnPressed = input;
}

void MouseInputComponent::privRegisterForOnHeld(const Input::Mouse& input)
{
	assert(onReleasedState == TrackingState::NotRegistered);
	SceneManagerAttorney::MouseInputControl::RegisterComponentInputOnHeld(this, input);
	onHeldState = TrackingState::RegisteredInput;
	enumIdOnHeld = input;
}

void MouseInputComponent::privRegisterForOnReleased(const Input::Mouse& input)
{
	assert(onReleasedState == TrackingState::NotRegistered);
	SceneManagerAttorney::MouseInputControl::RegisterComponentInputOnReleased(this, input);
	onReleasedState = TrackingState::RegisteredInput;
	enumIdOnReleased = input;
}

void MouseInputComponent::privRegisterForOnPressed(const InputActions& action)
{
	assert(onPressedState == TrackingState::NotRegistered);
	SceneManagerAttorney::MouseInputControl::RegisterComponentInputOnPressed(this, action);
	onPressedState = TrackingState::RegisteredAction;
	enumIdOnPressed = action;
}

void MouseInputComponent::privRegisterForOnHeld(const InputActions& action)
{
	assert(onHeldState == TrackingState::NotRegistered);
	SceneManagerAttorney::MouseInputControl::RegisterComponentInputOnHeld(this, action);
	onHeldState = TrackingState::RegisteredAction;
	enumIdOnHeld = action;
}

void MouseInputComponent::privRegisterForOnReleased(const InputActions& action)
{
	assert(onReleasedState == TrackingState::NotRegistered);
	SceneManagerAttorney::MouseInputControl::RegisterComponentInputOnReleased(this, action);
	onReleasedState = TrackingState::RegisteredAction;
	enumIdOnReleased = action;
}
#include "InputComponent.h"

//#include "Manager/InputManagerAttorney.h"
//
//#include <assert.h>
//
//InputComponent::InputComponent()
//{
//
//}
//
//InputComponent::~InputComponent()
//{
//	DeregisterFromInputAll();
//}
//
//void InputComponent::RegisterForInputAll(const InputTypes::PossibleKeys& input)
//{
//	RegisterForInputOnPressed(input);
//	RegisterForInputOnHeld(input);
//	RegisterForInputOnReleased(input);
//}
//
//void InputComponent::RegisterForInputOnPressed(const InputTypes::PossibleKeys& input)
//{
//	assert(onPressedState == TrackingState::NotRegistered);
//	InputManagerAttorney::InputComponentControls::RegisterInputComponentOnPress(this, input);
//	onPressedState = TrackingState::RegisteredInput;
//	enumIdOnPressed = input;
//}
//
//void InputComponent::RegisterForInputOnHeld(const InputTypes::PossibleKeys& input)
//{
//	assert(onHeldState == TrackingState::NotRegistered);
//	InputManagerAttorney::InputComponentControls::RegisterInputComponentOnHeld(this, input);
//	onHeldState = TrackingState::RegisteredInput;
//	enumIdOnHeld = input;
//}
//
//void InputComponent::RegisterForInputOnReleased(const InputTypes::PossibleKeys& input)
//{
//	assert(onReleasedState == TrackingState::NotRegistered);
//	InputManagerAttorney::InputComponentControls::RegisterInputComponentOnRelease(this, input);
//	onReleasedState = TrackingState::RegisteredInput;
//	enumIdOnReleased = input;
//}
//
//void InputComponent::RegisterForInputAll(const ActionsType::ActionsEnum& action)
//{
//	RegisterForInputOnPressed(action);
//	RegisterForInputOnHeld(action);
//	RegisterForInputOnReleased(action);
//}
//
//void InputComponent::RegisterForInputOnPressed(const ActionsType::ActionsEnum& action)
//{
//	assert(onPressedState == TrackingState::NotRegistered);
//	InputManagerAttorney::InputComponentControls::RegisterInputComponentOnPress(this, action);
//	onPressedState = TrackingState::RegisteredAction;
//	enumIdOnPressed = action;
//}
//
//void InputComponent::RegisterForInputOnHeld(const ActionsType::ActionsEnum& action)
//{
//	assert(onHeldState == TrackingState::NotRegistered);
//	InputManagerAttorney::InputComponentControls::RegisterInputComponentOnHeld(this, action);
//	onHeldState = TrackingState::RegisteredAction;
//	enumIdOnHeld = action;
//}
//
//void InputComponent::RegisterForInputOnReleased(const ActionsType::ActionsEnum& action)
//{
//	assert(onReleasedState == TrackingState::NotRegistered);
//	InputManagerAttorney::InputComponentControls::RegisterInputComponentOnRelease(this, action);
//	onReleasedState = TrackingState::RegisteredAction;
//	enumIdOnReleased = action;
//}
//
//void InputComponent::DeregisterFromInputAll()
//{
//	DeregisterFromInputOnPressed();
//	DeregisterFromInputOnHeld();
//	DeregisterFromInputOnReleased();
//}
//
//void InputComponent::DeregisterFromInputOnPressed()
//{
//	//assert(onPressedState != TrackingState::NotRegistered);
//
//	if (onPressedState == TrackingState::RegisteredAction)
//	{
//		InputManagerAttorney::InputComponentControls::DeregisterInputComponentOnPressAction(this, enumIdOnPressed);
//		onPressedState = TrackingState::NotRegistered;
//	}
//	else if(onPressedState == TrackingState::RegisteredInput)
//	{
//		InputManagerAttorney::InputComponentControls::DeregisterInputComponentOnPressInput(this, enumIdOnPressed);
//		onPressedState = TrackingState::NotRegistered;
//	}
//}
//
//void InputComponent::DeregisterFromInputOnHeld()
//{
//	//assert(onHeldState != TrackingState::NotRegistered);
//	if (onHeldState == TrackingState::RegisteredAction)
//	{
//		InputManagerAttorney::InputComponentControls::DeregisterInputComponentOnHeldAction(this, enumIdOnHeld);
//		onHeldState = TrackingState::NotRegistered;
//	}
//	else if(onHeldState == TrackingState::RegisteredInput)
//	{
//		InputManagerAttorney::InputComponentControls::DeregisterInputComponentOnHeldInput(this, enumIdOnHeld);
//		onHeldState = TrackingState::NotRegistered;
//	}
//}
//
//void InputComponent::DeregisterFromInputOnReleased()
//{
//	//assert(onReleasedState != TrackingState::NotRegistered);
//	if (onReleasedState == TrackingState::RegisteredAction)
//	{
//		InputManagerAttorney::InputComponentControls::DeregisterInputComponentOnReleaseAction(this, enumIdOnReleased);
//		onReleasedState = TrackingState::NotRegistered;
//	}
//	else if(onReleasedState == TrackingState::RegisteredInput)
//	{
//		InputManagerAttorney::InputComponentControls::DeregisterInputComponentOnReleaseInput(this, enumIdOnReleased);
//		onReleasedState = TrackingState::NotRegistered;
//	}
//}
//
//List<InputComponent>::Iterator& InputComponent::GetIteratorOnPressed()
//{
//	return iteratorOnPressed;
//}
//
//List<InputComponent>::Iterator& InputComponent::GetIteratorOnHeld()
//{
//	return iteratorOnHeld;
//}
//
//List<InputComponent>::Iterator& InputComponent::GetIteratorReleased()
//{
//	return iteratorOnReleased;
//}
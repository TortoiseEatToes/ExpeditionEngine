#ifndef InputComponent_H
#define InputComponent_H

//#include "Manager/InputManager.h"
//
//class InputComponent
//{
//public:
//	InputComponent();
//	InputComponent(const InputComponent& other) = delete;
//	InputComponent& operator= (const InputComponent& other) = delete;
//	~InputComponent();
//
//	void RegisterForInputAll(const InputTypes::PossibleKeys& input);
//	void RegisterForInputOnPressed(const InputTypes::PossibleKeys& input);
//	void RegisterForInputOnHeld(const InputTypes::PossibleKeys& input);
//	void RegisterForInputOnReleased(const InputTypes::PossibleKeys& input);
//
//	void RegisterForInputAll(const ActionsType::ActionsEnum& action);
//	void RegisterForInputOnPressed(const ActionsType::ActionsEnum& action);
//	void RegisterForInputOnHeld(const ActionsType::ActionsEnum& action);
//	void RegisterForInputOnReleased(const ActionsType::ActionsEnum& action);
//
//	void DeregisterFromInputAll();
//	void DeregisterFromInputOnPressed();
//	void DeregisterFromInputOnHeld();
//	void DeregisterFromInputOnReleased();
//
//protected:
//	virtual void OnPressed() {};
//	virtual void OnHeld() {};
//	virtual void OnReleased() {};
//
//private:
//	friend class InputComponentAttorney;
//
//	enum TrackingState
//	{
//		NotRegistered,
//		RegisteredAction,
//		RegisteredInput
//	};
//
//	List<InputComponent>::Iterator& GetIteratorOnPressed();
//	List<InputComponent>::Iterator& GetIteratorOnHeld();
//	List<InputComponent>::Iterator& GetIteratorReleased();
//	
//	List<InputComponent>::Iterator iteratorOnPressed;
//	List<InputComponent>::Iterator iteratorOnHeld;
//	List<InputComponent>::Iterator iteratorOnReleased;
//
//	TrackingState onPressedState = TrackingState::NotRegistered;
//	TrackingState onHeldState = TrackingState::NotRegistered;
//	TrackingState onReleasedState = TrackingState::NotRegistered;
//
//	int enumIdOnPressed = -1;
//	int enumIdOnHeld = -1;
//	int enumIdOnReleased = -1;
//};


#endif // !InputComponent_H
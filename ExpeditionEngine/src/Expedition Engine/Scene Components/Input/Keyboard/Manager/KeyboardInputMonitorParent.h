#pragma once

#include "../../../../Containers/List.h"

class KeyboardInputComponent;

class KeyboardInputMonitorParent
{
public:
	KeyboardInputMonitorParent();
	KeyboardInputMonitorParent(const KeyboardInputMonitorParent& other) = delete;
	KeyboardInputMonitorParent& operator= (const KeyboardInputMonitorParent& other) = delete;
	~KeyboardInputMonitorParent();

	void RegisterForOnPressed(KeyboardInputComponent* InputComponentToRegister);
	void RegisterForOnHeld(KeyboardInputComponent* InputComponentToRegister);
	void RegisterForOnReleased(KeyboardInputComponent* InputComponentToRegister);

	void DeregisterFromOnPressed(KeyboardInputComponent* InputComponentToRemove);
	void DeregisterFromOnHeld(KeyboardInputComponent* InputComponentToRemove);
	void DeregisterFromOnReleased(KeyboardInputComponent* InputComponentToRemove);

	virtual void IncrementRefCount() = 0;
	virtual void DecrementRefCount() = 0;

	void ProcessOnPressedEvent();
	void ProcessOnHeldEvent();
	void ProcessOnReleasedEvent();

protected:
	List<KeyboardInputComponent*> eventListOnPressed;
	List<KeyboardInputComponent*> eventListOnHeld;
	List<KeyboardInputComponent*> eventListOnReleased;
	List<KeyboardInputComponent*>::Iterator iterator;
	int refCount = 0;
};
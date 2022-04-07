#pragma once

#include "../../../../Containers/List.h"

class MouseInputComponent;

class MouseInputMonitorParent
{
public:
	MouseInputMonitorParent();
	MouseInputMonitorParent(const MouseInputMonitorParent& other) = delete;
	MouseInputMonitorParent& operator= (const MouseInputMonitorParent& other) = delete;
	~MouseInputMonitorParent();

	void RegisterForOnPressed(MouseInputComponent* InputComponentToRegister);
	void RegisterForOnHeld(MouseInputComponent* InputComponentToRegister);
	void RegisterForOnReleased(MouseInputComponent* InputComponentToRegister);

	void DeregisterFromOnPressed(MouseInputComponent* InputComponentToRemove);
	void DeregisterFromOnHeld(MouseInputComponent* InputComponentToRemove);
	void DeregisterFromOnReleased(MouseInputComponent* InputComponentToRemove);

	virtual void IncrementRefCount() = 0;
	virtual void DecrementRefCount() = 0;

	void ProcessOnPressedEvent();
	void ProcessOnHeldEvent();
	void ProcessOnReleasedEvent();

protected:
	List<MouseInputComponent*> eventListOnPressed;
	List<MouseInputComponent*> eventListOnHeld;
	List<MouseInputComponent*> eventListOnReleased;
	List<MouseInputComponent*>::Iterator iterator;
	int refCount = 0;
};
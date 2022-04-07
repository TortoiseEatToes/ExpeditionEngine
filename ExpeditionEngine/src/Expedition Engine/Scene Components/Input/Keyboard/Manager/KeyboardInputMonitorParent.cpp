#include "KeyboardInputMonitorParent.h"

#include "../KeyboardInputComponentAttorney.h"

KeyboardInputMonitorParent::KeyboardInputMonitorParent()
{
}

KeyboardInputMonitorParent::~KeyboardInputMonitorParent()
{
}

void KeyboardInputMonitorParent::RegisterForOnPressed(KeyboardInputComponent* pInputComponentToRegister)
{
	eventListOnPressed.PushBack(pInputComponentToRegister, KeyboardInputComponentAttorney::MonitorParentControl::GetIteratorOnPressed(pInputComponentToRegister));
	IncrementRefCount();
}

void KeyboardInputMonitorParent::RegisterForOnHeld(KeyboardInputComponent* pInputComponentToRegister)
{
	eventListOnHeld.PushBack(pInputComponentToRegister, KeyboardInputComponentAttorney::MonitorParentControl::GetIteratorOnHeld(pInputComponentToRegister));
	IncrementRefCount();
}

void KeyboardInputMonitorParent::RegisterForOnReleased(KeyboardInputComponent* pInputComponentToRegister)
{
	eventListOnReleased.PushBack(pInputComponentToRegister, KeyboardInputComponentAttorney::MonitorParentControl::GetIteratorOnReleased(pInputComponentToRegister));
	IncrementRefCount();
}

void KeyboardInputMonitorParent::DeregisterFromOnPressed(KeyboardInputComponent* pInputComponentToRegister)
{
	eventListOnPressed.Remove(KeyboardInputComponentAttorney::MonitorParentControl::GetIteratorOnPressed(pInputComponentToRegister));
	DecrementRefCount();
}

void KeyboardInputMonitorParent::DeregisterFromOnHeld(KeyboardInputComponent* pInputComponentToRegister)
{
	eventListOnHeld.Remove(KeyboardInputComponentAttorney::MonitorParentControl::GetIteratorOnHeld(pInputComponentToRegister));
	DecrementRefCount();
}

void KeyboardInputMonitorParent::DeregisterFromOnReleased(KeyboardInputComponent* pInputComponentToRegister)
{
	eventListOnReleased.Remove(KeyboardInputComponentAttorney::MonitorParentControl::GetIteratorOnReleased(pInputComponentToRegister));
	DecrementRefCount();
}

void KeyboardInputMonitorParent::ProcessOnPressedEvent()
{
	eventListOnPressed.SetFront(iterator);

	while (!iterator.IsOutOfNodes())
	{
		KeyboardInputComponentAttorney::MonitorParentControl::ExecuteOnPressed(iterator.GetCurrentObject());
		++iterator;
	}
}

void KeyboardInputMonitorParent::ProcessOnHeldEvent()
{
	eventListOnHeld.SetFront(iterator);

	while (!iterator.IsOutOfNodes())
	{
		KeyboardInputComponentAttorney::MonitorParentControl::ExecuteOnHeld(iterator.GetCurrentObject());
		++iterator;
	}
}

void KeyboardInputMonitorParent::ProcessOnReleasedEvent()
{
	eventListOnReleased.SetFront(iterator);

	while (!iterator.IsOutOfNodes())
	{
		KeyboardInputComponentAttorney::MonitorParentControl::ExecuteOnReleased(iterator.GetCurrentObject());
		++iterator;
	}
}

#include "MouseInputMonitorParent.h"

#include "../MouseInputComponentAttorney.h"

MouseInputMonitorParent::MouseInputMonitorParent()
{
}

MouseInputMonitorParent::~MouseInputMonitorParent()
{
}

void MouseInputMonitorParent::RegisterForOnPressed(MouseInputComponent* pInputComponentToRegister)
{
	eventListOnPressed.PushBack(pInputComponentToRegister, MouseInputComponentAttorney::MonitorParentControl::GetIteratorOnPressed(pInputComponentToRegister));
	IncrementRefCount();
}

void MouseInputMonitorParent::RegisterForOnHeld(MouseInputComponent* pInputComponentToRegister)
{
	eventListOnHeld.PushBack(pInputComponentToRegister, MouseInputComponentAttorney::MonitorParentControl::GetIteratorOnHeld(pInputComponentToRegister));
	IncrementRefCount();
}

void MouseInputMonitorParent::RegisterForOnReleased(MouseInputComponent* pInputComponentToRegister)
{
	eventListOnReleased.PushBack(pInputComponentToRegister, MouseInputComponentAttorney::MonitorParentControl::GetIteratorOnReleased(pInputComponentToRegister));
	IncrementRefCount();
}

void MouseInputMonitorParent::DeregisterFromOnPressed(MouseInputComponent* pInputComponentToRegister)
{
	eventListOnPressed.Remove(MouseInputComponentAttorney::MonitorParentControl::GetIteratorOnPressed(pInputComponentToRegister));
	DecrementRefCount();
}

void MouseInputMonitorParent::DeregisterFromOnHeld(MouseInputComponent* pInputComponentToRegister)
{
	eventListOnHeld.Remove(MouseInputComponentAttorney::MonitorParentControl::GetIteratorOnHeld(pInputComponentToRegister));
	DecrementRefCount();
}

void MouseInputMonitorParent::DeregisterFromOnReleased(MouseInputComponent* pInputComponentToRegister)
{
	eventListOnReleased.Remove(MouseInputComponentAttorney::MonitorParentControl::GetIteratorOnReleased(pInputComponentToRegister));
	DecrementRefCount();
}

void MouseInputMonitorParent::ProcessOnPressedEvent()
{
	eventListOnPressed.SetFront(iterator);

	while (!iterator.IsOutOfNodes())
	{
		MouseInputComponentAttorney::MonitorParentControl::ExecuteOnPressed(iterator.GetCurrentObject());
		++iterator;
	}
}

void MouseInputMonitorParent::ProcessOnHeldEvent()
{
	eventListOnHeld.SetFront(iterator);

	while (!iterator.IsOutOfNodes())
	{
		MouseInputComponentAttorney::MonitorParentControl::ExecuteOnHeld(iterator.GetCurrentObject());
		++iterator;
	}
}

void MouseInputMonitorParent::ProcessOnReleasedEvent()
{
	eventListOnReleased.SetFront(iterator);

	while (!iterator.IsOutOfNodes())
	{
		MouseInputComponentAttorney::MonitorParentControl::ExecuteOnReleased(iterator.GetCurrentObject());
		++iterator;
	}
}

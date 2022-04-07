#include "MouseKeyMonitor.h"

#include "MouseActionMonitor.h"
#include "MouseInputManager.h"

#include "MouseInputManager.h"

MouseKeyMonitor::MouseKeyMonitor(const int& virtualKeyCode)
{
	keyCode = virtualKeyCode;
}

void MouseKeyMonitor::UpdateState(const bool& isCurrentlyPressed)
{
	if (isCurrentlyPressed)
	{
		//The key is pressed currently
		if (isPressed)
		{
			ProcessOnHeldEvent();
			if (boundAction != nullptr)
			{
				boundAction->OnHeld();
			}
		}
		else
		{
			ProcessOnPressedEvent();
			if (boundAction != nullptr)
			{
				boundAction->OnPressed();
			}
			isPressed = true;
		}

	}
	else if (isPressed)
	{
		ProcessOnReleasedEvent();
		if (boundAction != nullptr)
		{
			boundAction->OnReleased();
		}
		isPressed = false;
	}
}

void MouseKeyMonitor::SetKeyCode(const int& newKeyCode)
{
	keyCode = newKeyCode;
}

void MouseKeyMonitor::BindAction(MouseActionMonitor* action)
{
	if (boundAction != nullptr && boundAction != action)
	{
		UnbindFromAction();
	}

	boundAction = action;
}

void MouseKeyMonitor::UnbindFromAction()
{
	boundAction->UnBindFromKey();
	boundAction = nullptr;
}

void MouseKeyMonitor::IncrementRefCount()
{
	if (++refCount == 1)
	{
		pMouseInputManager->RegisterKeyMonitorToTracking(this);
	}
}

void MouseKeyMonitor::DecrementRefCount()
{
	if (--refCount == 0)
	{
		pMouseInputManager->DeregisterKeyMonitorFromTracking(this);
	}
}

List<MouseKeyMonitor*>::Iterator& MouseKeyMonitor::GetStorageIterator()
{
	return storageIterator;
}

const int& MouseKeyMonitor::GetCode() const
{
	return keyCode;
}

void MouseKeyMonitor::SetInputManager(MouseInputManager* pManager)
{
	pMouseInputManager = pManager;
}

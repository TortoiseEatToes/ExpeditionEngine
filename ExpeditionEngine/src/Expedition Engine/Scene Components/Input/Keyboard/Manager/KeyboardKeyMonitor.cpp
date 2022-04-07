#include "KeyboardKeyMonitor.h"

#include "KeyboardActionMonitor.h"

#include "KeyboardInputManager.h"

KeyboardKeyMonitor::KeyboardKeyMonitor(const int& virtualKeyCode)
{
	keyCode = virtualKeyCode;
}

void KeyboardKeyMonitor::UpdateState(const bool& isCurrentlyPressed)
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

void KeyboardKeyMonitor::SetKeyCode(const int& newKeyCode)
{
	keyCode = newKeyCode;
}

void KeyboardKeyMonitor::BindAction(KeyboardActionMonitor* action)
{
	if (boundAction != nullptr && boundAction != action)
	{
		UnbindFromAction();
	}

	boundAction = action;
}

void KeyboardKeyMonitor::UnbindFromAction()
{
	boundAction->UnBindFromKey();
	boundAction = nullptr;
}

void KeyboardKeyMonitor::IncrementRefCount()
{
	if (++refCount == 1)
	{
		pKeyboardInputManager->RegisterKeyMonitorToTracking(*this);
	}
}

void KeyboardKeyMonitor::DecrementRefCount()
{
	if (--refCount == 0)
	{
		pKeyboardInputManager->DeregisterKeyMonitorFromTracking(*this);
	}
}

List<KeyboardKeyMonitor*>::Iterator& KeyboardKeyMonitor::GetStorageIterator()
{
	return storageIterator;
}

const int& KeyboardKeyMonitor::GetCode() const
{
	return keyCode;
}

void KeyboardKeyMonitor::SetInputManager(KeyboardInputManager* pManager)
{
	pKeyboardInputManager = pManager;
}

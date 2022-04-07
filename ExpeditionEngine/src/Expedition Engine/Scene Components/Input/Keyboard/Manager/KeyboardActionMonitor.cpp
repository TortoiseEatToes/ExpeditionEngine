#include "KeyboardActionMonitor.h"

#include "KeyboardKeyMonitor.h"

void KeyboardActionMonitor::OnPressed()
{
	ProcessOnPressedEvent();
}

void KeyboardActionMonitor::OnHeld()
{
	ProcessOnHeldEvent();
}

void KeyboardActionMonitor::OnReleased()
{
	ProcessOnReleasedEvent();
}

void KeyboardActionMonitor::BindToKey(KeyboardKeyMonitor* userKey)
{
	if (boundKey != nullptr)
	{
		UnBindFromKey();
	}

	boundKey = userKey;

	//TODO: talk to sara about changing her code

	//if (refCount > 0)
	{
		//boundKey->IncrementRefCount();
		boundKey->BindAction(this);
	}
}

void KeyboardActionMonitor::UnBindFromKey()
{
	if (boundKey != nullptr && refCount > 0)
	{
		boundKey->DecrementRefCount();
	}
	boundKey = nullptr;
}

void KeyboardActionMonitor::IncrementRefCount()
{
	if (++refCount == 1 && boundKey != nullptr)
	{
		boundKey->IncrementRefCount();
	}
}

void KeyboardActionMonitor::DecrementRefCount()
{
	if (--refCount == 0 && boundKey != nullptr)
	{
		boundKey->DecrementRefCount();
	}
}

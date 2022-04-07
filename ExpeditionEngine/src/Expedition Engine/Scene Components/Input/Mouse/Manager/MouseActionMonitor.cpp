#include "MouseActionMonitor.h"

#include "MouseKeyMonitor.h"

void MouseActionMonitor::OnPressed()
{
	ProcessOnPressedEvent();
}

void MouseActionMonitor::OnHeld()
{
	ProcessOnHeldEvent();
}

void MouseActionMonitor::OnReleased()
{
	ProcessOnReleasedEvent();
}

void MouseActionMonitor::BindToKey(MouseKeyMonitor* userKey)
{
	if (boundKey != nullptr)
	{
		UnBindFromKey();
	}

	boundKey = userKey;
	if (refCount > 0)
	{
		boundKey->IncrementRefCount();
		boundKey->BindAction(this);
	}
}

void MouseActionMonitor::UnBindFromKey()
{
	if (boundKey != nullptr && refCount > 0)
	{
		boundKey->DecrementRefCount();
	}
	boundKey = nullptr;
}

void MouseActionMonitor::IncrementRefCount()
{
	if (++refCount == 1 && boundKey != nullptr)
	{
		boundKey->IncrementRefCount();
	}
}

void MouseActionMonitor::DecrementRefCount()
{
	if (--refCount == 0 && boundKey != nullptr)
	{
		boundKey->DecrementRefCount();
	}
}

#pragma once

#include "KeyboardInputMonitorParent.h"

class MouseInputComponent;
class KeyboardKeyMonitor;

class KeyboardActionMonitor : public KeyboardInputMonitorParent
{
public:
	KeyboardActionMonitor() = default;
	KeyboardActionMonitor(const KeyboardActionMonitor&) = delete;
	KeyboardActionMonitor& operator= (const KeyboardActionMonitor&) = delete;
	~KeyboardActionMonitor() = default;

	void OnPressed();
	void OnHeld();
	void OnReleased();

	void BindToKey(KeyboardKeyMonitor* userKey);
	void UnBindFromKey();

	virtual void IncrementRefCount();
	virtual void DecrementRefCount();

private:

	KeyboardKeyMonitor* boundKey = nullptr;
};
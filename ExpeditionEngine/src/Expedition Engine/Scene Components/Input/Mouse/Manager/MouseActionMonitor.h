#pragma once

#include "MouseInputMonitorParent.h"

class MouseInputComponent;
class MouseKeyMonitor;

class MouseActionMonitor : public MouseInputMonitorParent
{
public:
	MouseActionMonitor() = default;
	MouseActionMonitor(const MouseActionMonitor&) = delete;
	MouseActionMonitor& operator= (const MouseActionMonitor&) = delete;
	~MouseActionMonitor() = default;

	void OnPressed();
	void OnHeld();
	void OnReleased();

	void BindToKey(MouseKeyMonitor* userKey);
	void UnBindFromKey();

	virtual void IncrementRefCount();
	virtual void DecrementRefCount();

private:

	MouseKeyMonitor* boundKey = nullptr;
};
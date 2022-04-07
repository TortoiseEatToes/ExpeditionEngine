#pragma once

#include "MouseInputMonitorParent.h"

class MouseInputComponent;
class MouseActionMonitor;
class MouseInputManager;

class MouseKeyMonitor : public MouseInputMonitorParent
{
public:
	MouseKeyMonitor() = default;
	MouseKeyMonitor(const int& virtualKeyCode);
	MouseKeyMonitor(const MouseKeyMonitor&) = delete;
	MouseKeyMonitor& operator= (const MouseKeyMonitor&) = delete;
	~MouseKeyMonitor() = default;

	void UpdateState(const bool& isCurrentlyPressed);

	void SetKeyCode(const int& newKeyCode);

	void BindAction(MouseActionMonitor* action);
	void UnbindFromAction();

	virtual void IncrementRefCount();
	virtual void DecrementRefCount();

	List<MouseKeyMonitor*>::Iterator& GetStorageIterator();

	const int& GetCode() const;

	void SetInputManager(MouseInputManager* pManager);

private:
	List<MouseKeyMonitor*>::Iterator storageIterator;
	MouseActionMonitor* boundAction = nullptr;
	MouseInputManager* pMouseInputManager;
	int keyCode = 65;
	bool isPressed = false;
};
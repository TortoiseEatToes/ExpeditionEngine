#pragma once

#include "KeyboardInputMonitorParent.h"

class KeyboardActionMonitor;
class KeyboardInputManager;

class KeyboardKeyMonitor : public KeyboardInputMonitorParent
{
public:
	KeyboardKeyMonitor() = default;
	KeyboardKeyMonitor(const int& virtualKeyCode);
	KeyboardKeyMonitor(const KeyboardKeyMonitor&) = delete;
	KeyboardKeyMonitor& operator= (const KeyboardKeyMonitor&) = delete;
	~KeyboardKeyMonitor() = default;

	void UpdateState(const bool& isCurrentlyPressed);

	void SetKeyCode(const int& newKeyCode);

	void BindAction(KeyboardActionMonitor* action);
	void UnbindFromAction();

	virtual void IncrementRefCount();
	virtual void DecrementRefCount();

	List<KeyboardKeyMonitor*>::Iterator& GetStorageIterator();

	const int& GetCode() const;

	void SetInputManager(KeyboardInputManager* pManager);

private:
	List<KeyboardKeyMonitor*>::Iterator storageIterator;
	KeyboardActionMonitor* boundAction = nullptr;
	KeyboardInputManager* pKeyboardInputManager;
	int keyCode = 65;
	bool isPressed = false;
};
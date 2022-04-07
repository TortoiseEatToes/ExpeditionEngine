#pragma once

#include "../KeyboardInputComponent.h"

#include "KeyboardKeyMonitor.h"
#include "KeyboardActionMonitor.h"

#include "../../Input.h"

class KeyboardKeyMonitor;
struct ActionBindingSetting;

class KeyboardInputManager
{
public:
	KeyboardInputManager();
	KeyboardInputManager(const KeyboardInputManager& other) = delete;
	KeyboardInputManager& operator= (const KeyboardInputManager& other) = delete;
	~KeyboardInputManager();

	/// <summary>Called once per frame by the scene that owns this manager.</summary>
	void ProcessKeyboardInput();

	void RegisterComponentOnPressedKey(KeyboardInputComponent*& KeyboardInputComponent, const int& keyIndex);
	void RegisterComponentOnHeldKey(KeyboardInputComponent*& KeyboardInputComponent, const int& keyIndex);
	void RegisterComponentOnReleasedKey(KeyboardInputComponent*& KeyboardInputComponent, const int& keyIndex);

	void RegisterComponentOnPressedAction(KeyboardInputComponent*& KeyboardInputComponent, const int& actionIndex);
	void RegisterComponentOnHeldAction(KeyboardInputComponent*& KeyboardInputComponent, const int& actionIndex);
	void RegisterComponentOnReleasedAction(KeyboardInputComponent*& KeyboardInputComponent, const int& actionIndex);

	void DeregisterComponentOnPressedKey(KeyboardInputComponent*& KeyboardInputComponent, const int& keyIndex);
	void DeregisterComponentOnHeldKey(KeyboardInputComponent*& KeyboardInputComponent, const int& keyIndex);
	void DeregisterComponentOnReleasedKey(KeyboardInputComponent*& KeyboardInputComponent, const int& keyIndex);

	void DeregisterComponentOnPressedAction(KeyboardInputComponent*& KeyboardInputComponent, const int& actionIndex);
	void DeregisterComponentOnHeldAction(KeyboardInputComponent*& KeyboardInputComponent, const int& actionIndex);
	void DeregisterComponentOnReleasedAction(KeyboardInputComponent*& KeyboardInputComponent, const int& actionIndex);

	void RegisterKeyMonitorToTracking(KeyboardKeyMonitor& pKeyMonitor);
	void DeregisterKeyMonitorFromTracking(KeyboardKeyMonitor& pKeyMonitor);

	/// <summary>This is called whenever the user changes a key bindings or the scene change triggers rebinding.</summary>
	/// <param name="actionIndex">The index of the keyboard input key to bind</param>
	/// <param name="actionBindingSetting">The action to bind the key to</param>
	void BindAction(const int& actionIndex, const ActionBindingSetting& actionBindingSetting);

private:

	/// <summary>This is a helper function to initialize all of the KeyboardKeyMonitor.</summary>
	/// <param name="pKeyMonitor">Reference to the current key monitor to initalize</param>
	/// <param name="keyCode">The bit mask value that the keyboard key monitor should use</param>
	void Initialize(KeyboardKeyMonitor& keyboardKeyMonitor, const int& keyCode);

	KeyboardActionMonitor userActions[NumberOfActions];
	KeyboardKeyMonitor userInputKeys[NumberOfKeyboardKeys];

	List<KeyboardKeyMonitor*> inputKeysToTrack;
	List<KeyboardKeyMonitor*>::Iterator iterator;
	KeyboardInputComponent* pCurrentComponent;
};
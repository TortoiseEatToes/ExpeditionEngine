#pragma once

#include "../../../../../Expedition Resources/Actions.h"
#include "../../Input.h"
#include "../../Manager/InputManager.h"

#include "MouseActionMonitor.h"
#include "MouseKeyMonitor.h"

class MouseInputComponent;
class MouseKeyMonitor;
struct ActionBindingSetting;

class MouseInputManager
{
public:
	MouseInputManager();
	MouseInputManager(const MouseInputManager& other) = delete;
	MouseInputManager& operator= (const MouseInputManager& other) = delete;
	~MouseInputManager();

	/// <summary>Called once per frame by the scene that owns this manager.</summary>
	void ProcessMouseInput();

	void RegisterComponentOnPressedKey(MouseInputComponent* MouseInputComponent, const int& keyIndex);
	void RegisterComponentOnHeldKey(MouseInputComponent* MouseInputComponent, const int& keyIndex);
	void RegisterComponentOnReleasedKey(MouseInputComponent* MouseInputComponent, const int& keyIndex);

	void RegisterComponentOnPressedAction(MouseInputComponent* MouseInputComponent, const int& actionIndex);
	void RegisterComponentOnHeldAction(MouseInputComponent* MouseInputComponent, const int& actionIndex);
	void RegisterComponentOnReleasedAction(MouseInputComponent* MouseInputComponent, const int& actionIndex);

	void DeregisterComponentOnPressedKey(MouseInputComponent* MouseInputComponent, const int& keyIndex);
	void DeregisterComponentOnHeldKey(MouseInputComponent* MouseInputComponent, const int& keyIndex);
	void DeregisterComponentOnReleasedKey(MouseInputComponent* MouseInputComponent, const int& keyIndex);

	void DeregisterComponentOnPressedAction(MouseInputComponent* MouseInputComponent, const int& actionIndex);
	void DeregisterComponentOnHeldAction(MouseInputComponent* MouseInputComponent, const int& actionIndex);
	void DeregisterComponentOnReleasedAction(MouseInputComponent* MouseInputComponent, const int& actionIndex);

	void RegisterKeyMonitorToTracking(MouseKeyMonitor* pKeyMonitor);
	void DeregisterKeyMonitorFromTracking(MouseKeyMonitor* pKeyMonitor);

	/// <summary>This is called whenever the user changes a key bindings or the scene change triggers rebinding.</summary>
	/// <param name="actionIndex">The index of the mouse input key to bind</param>
	/// <param name="actionBindingSetting">The action to bind the key to</param>
	void BindAction(const int& actionIndex, const ActionBindingSetting& actionBindingSetting);

private:

	/// <summary>This is a helper function to initialize all of the MouseKeyMonitors.</summary>
	/// <param name="pKeyMonitor">Reference to the current key monitor to initalize</param>
	/// <param name="keyCode">The bit mask value that the mouse key monitor should use</param>
	void Initialize(MouseKeyMonitor& keyMonitor, const int& keyCode);

	MouseActionMonitor userActions[NumberOfActions];
	MouseKeyMonitor userInputKeys[NumberOfMouseKeys];

	List<MouseKeyMonitor*> inputKeysToTrack;
	List<MouseKeyMonitor*>::Iterator iterator;
	MouseInputComponent* pCurrentComponent;
};
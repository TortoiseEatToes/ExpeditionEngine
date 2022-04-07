#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "../Input.h"
#include "../../../../Expedition Resources/Actions.h"
#include "ActionBindingSetting.h"

class KeyboardInputManager;
class MouseInputManager;

class InputManager
{
public:
	/// <summary>Bind a specific keyboard input key to an action.</summary>
	/// <param name="input">The keyboard input key to bind</param>
	/// <param name="action">The action to bind the given key to</param>
	static void Bind(const Input::Keyboard input, const InputActions action)
	{
		Instance().privBind(input, action);
	}

	/// <summary>Bind a specific mouse input key to an action.</summary>
	/// <param name="input">The mouse input key to bind</param>
	/// <param name="action">The action to bind the given key to</param>
	static void Bind(const Input::Mouse input, const InputActions action)
	{
		Instance().privBind(input, action);
	}

	/// <summary>Get the X coordinate of the mouse position.</summary>
	/// <returns>int X component of the mouse Position</returns> 
	static const int& GetMouseXPosition()
	{
		return Instance().privGetMouseXPosition();
	}

	/// <summary>Get the Y coordinate of the mouse position.</summary>
	/// <returns>int Y component of the mouse Position</returns> 
	static const int& GetMouseYPosition()
	{
		return Instance().privGetMouseYPosition();
	}

private:
	friend class InputManagerAttorney;

	InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator= (const InputManager&) = delete;
	~InputManager();

	static InputManager* pInstance;

	static void Initialize()
	{
		pInstance = new InputManager();
	}

	static InputManager& Instance()
	{
		return *pInstance;
	}

	static void Terminate()
	{
		delete pInstance;
	}

	/// <summary>Change all of the action bindings for this manager to match the current version.</summary>
	/// <param name="keyboardInputManager">The keyboard manager that needs to be updated</param>
	static void UpdateManagerBindings(KeyboardInputManager& keyboardInputManager)
	{
		Instance().privUpdateManagerBindings(keyboardInputManager);
	}
	void privUpdateManagerBindings(KeyboardInputManager& keyboardInputManager);

	/// <summary>Change all of the action bindings for this manager to match the current version.</summary>
	/// <param name="mouseInputManager">The mouse manager that needs to be updated</param>
	static void UpdateManagerBindings(MouseInputManager& mouseInputManager)
	{
		Instance().privUpdateManagerBindings(mouseInputManager);
	}
	void privUpdateManagerBindings(MouseInputManager& mouseInputManager);

	void privBind(const Input::Keyboard input, const InputActions action);
	void privBind(const Input::Mouse input, const InputActions action);

	const int& privGetMouseXPosition();
	const int& privGetMouseYPosition();

	/// <summary>The MainWindow calls this when the mouse moves.</summary>
	/// <param name="posX">X position of the mouse</param>
	/// <param name="posY">Y position of the mouse</param>
	static void SetMousePosition(const int& posX, const int& posY)
	{
		Instance().privSetMousePosition(posX, posY);
	}
	void privSetMousePosition(const int& posX, const int& posY);

	ActionBindingSetting actionBindingSettings[NumberOfActions];
	KeyboardInputManager* pCurrentKeyboardInputManager;
	MouseInputManager* pCurrentMouseInputManager;
	int mousePosX = -1;
	int mousePosY = -1;
};

#endif // !INPUTMANAGER_H
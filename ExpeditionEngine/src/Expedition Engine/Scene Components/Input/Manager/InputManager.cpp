#include "InputManager.h"

InputManager* InputManager::pInstance = nullptr;

#include "../Keyboard/Manager/KeyboardInputManager.h"
#include "../Mouse/Manager/MouseInputManager.h"
#include "../../../DX12App/DXApp/DXApp_12.h"

InputManager::InputManager()
{
	LPPOINT point = new tagPOINT();

	GetCursorPos(point);

	mousePosX = point->x;
	mousePosY = point->y;

	delete point;
}

void InputManager::privUpdateManagerBindings(KeyboardInputManager& keyboardInputManager)
{
	pCurrentKeyboardInputManager = &keyboardInputManager;

	for (int i = 0; i < NumberOfActions; ++i)
	{
		keyboardInputManager.BindAction(i, actionBindingSettings[i]);
	}
}

void InputManager::privUpdateManagerBindings(MouseInputManager& mouseInputManager)
{
	pCurrentMouseInputManager = &mouseInputManager;

	for (int i = 0; i < NumberOfActions; ++i)
	{
		mouseInputManager.BindAction(i, actionBindingSettings[i]);
	}
}

void InputManager::privBind(const Input::Keyboard key, const InputActions action)
{
	actionBindingSettings[action].index = key;
	actionBindingSettings[action].actionBindingType = ActionBindingSetting::Type::Keyboard;
	

	if (pCurrentKeyboardInputManager != nullptr)
	{
		pCurrentKeyboardInputManager->BindAction(action, actionBindingSettings[action]);
	}
	if (pCurrentMouseInputManager != nullptr)
	{
		pCurrentMouseInputManager->BindAction(action, actionBindingSettings[action]);
	}
}

void InputManager::privBind(const Input::Mouse mouse, const InputActions action)
{
	actionBindingSettings[action].actionBindingType = ActionBindingSetting::Type::Mouse;
	actionBindingSettings[action].index = mouse;

	if (pCurrentKeyboardInputManager != nullptr)
	{
		pCurrentKeyboardInputManager->BindAction(action, actionBindingSettings[action]);
	}
	if (pCurrentMouseInputManager != nullptr)
	{
		pCurrentMouseInputManager->BindAction(action, actionBindingSettings[action]);
	}
}

const int& InputManager::privGetMouseXPosition()
{
	return mousePosX;
}

const int& InputManager::privGetMouseYPosition()
{
	return mousePosY;
}

void InputManager::privSetMousePosition(const int& posX, const int& posY)
{
	mousePosX = posX;
	mousePosY = posY;
}

InputManager::~InputManager()
{

}
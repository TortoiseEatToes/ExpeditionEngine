#ifndef INPUTMANAGERTTORNEY_H
#define INPUTMANAGERATTORNEY_H

#include "InputManager.h"

class InputManagerAttorney
{
public:

	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void Initialize()
		{
			InputManager::Initialize();
		}

		static void Terminate()
		{
			InputManager::Terminate();
		}
	};

	class EngineSceneControl
	{
	private:
		friend class EngineScene;

		static void UpdateManagerBindings(KeyboardInputManager& keyboardInputManager)
		{
			InputManager::UpdateManagerBindings(keyboardInputManager);
		}

		static void UpdateManagerBindings(MouseInputManager& mouseInputManager)
		{
			InputManager::UpdateManagerBindings(mouseInputManager);
		}
	};

	class MainWindowControl
	{
	private:
		friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static void SetMousePosition(const int& posX, const int& posY)
		{
			InputManager::SetMousePosition(posX, posY);
		}
	};

};

#endif // !INPUTMANAGERATTORNEY_H

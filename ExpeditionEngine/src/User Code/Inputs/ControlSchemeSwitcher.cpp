#include "ControlSchemeSwitcher.h"

#include "../../Expedition Engine/Scene Components/Input/Manager/InputManager.h"

#include <stdio.h>

ControlSchemeSwitcher::ControlSchemeSwitcher()
{
}

ControlSchemeSwitcher::~ControlSchemeSwitcher()
{
	
}

void ControlSchemeSwitcher::OnKeyPressed()
{
	printf("\nSwapping Control Schemes\n");
	if (!isCurrentStateWASD)
	{
		InputManager::Bind(Input::LetterKeyW, InputActions::MoveForward);
		InputManager::Bind(Input::LetterKeyS, InputActions::MoveBackward);
		InputManager::Bind(Input::LetterKeyA, InputActions::MoveLeft);
		InputManager::Bind(Input::LetterKeyD, InputActions::MoveRight);
	}
	else
	{
		InputManager::Bind(Input::ArrowUp, InputActions::MoveForward);
		InputManager::Bind(Input::ArrowDown, InputActions::MoveBackward);
		InputManager::Bind(Input::ArrowLeft, InputActions::MoveLeft);
		InputManager::Bind(Input::ArrowRight, InputActions::MoveRight);
	}

	isCurrentStateWASD = !isCurrentStateWASD;
}

void ControlSchemeSwitcher::OnKeyHeld()
{

}

void ControlSchemeSwitcher::OnKeyReleased()
{

}

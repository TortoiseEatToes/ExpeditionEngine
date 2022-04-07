#include "Footstep_Controller.h"
#include "../../Expedition Engine/Scene Components/Input/Manager/InputManager.h"

Footstep_Controller::Footstep_Controller(SceneName sceneName) : GameObject(sceneName)
{
}

Footstep_Controller::~Footstep_Controller()
{
}

void Footstep_Controller::OnSceneEnter()
{
	input.RegisterForOnPressed(GetRegisteredScene(), InputActions::PlayerMove);
	input.RegisterForOnReleased(GetRegisteredScene(), InputActions::PlayerMove);

	InputManager::Bind(Input::Keyboard::LetterKeyW, InputActions::PlayerMove);
	InputManager::Bind(Input::Keyboard::LetterKeyD, InputActions::PlayerMove);
	InputManager::Bind(Input::Keyboard::LetterKeyS, InputActions::PlayerMove);
	InputManager::Bind(Input::Keyboard::LetterKeyA, InputActions::PlayerMove);
}

void Footstep_Controller::OnSceneExit()
{
	input.DeregisterFromOnPressed();
	input.DeregisterFromOnReleased();
}

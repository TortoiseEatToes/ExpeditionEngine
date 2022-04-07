#include "PlayerControllerQuitGame.h"

#include "../../Expedition Engine/Engine/ExpeditionEngine.h"
#include <stdio.h>


PlayerControllerQuitGame::PlayerControllerQuitGame()
{
}

PlayerControllerQuitGame::~PlayerControllerQuitGame()
{
}

void PlayerControllerQuitGame::OnKeyPressed()
{
	ExpeditionEngine::Quit();
}

void PlayerControllerQuitGame::OnKeyHeld()
{
}

void PlayerControllerQuitGame::OnKeyReleased()
{
}

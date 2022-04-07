#include "Input_CameraFwdBack.h"

#include "../../Expedition Engine/Scenes/SceneManager.h"
#include "../../Expedition Engine/Camera/Camera.h"

void Input_CameraFwdBack::OnKeyHeld()
{
	SceneManager::GetCurrentPerspectiveCamera()->TranslateFwdBack(speed);
	SceneManager::GetCurrentPerspectiveCamera()->Update();
}

#include "Input_CameraLeftRight.h"

#include "../../Expedition Engine/Scenes/SceneManager.h"
#include "../../Expedition Engine/Camera/Camera.h"

void Input_CameraLeftRight::OnKeyHeld()
{
	SceneManager::GetCurrentPerspectiveCamera()->TranslateLeftRight(speed);
	SceneManager::GetCurrentPerspectiveCamera()->Update();
}

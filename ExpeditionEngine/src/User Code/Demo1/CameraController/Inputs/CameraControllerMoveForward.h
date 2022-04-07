#ifndef CAMERACONTROLLERMOVEFORWARD_H
#define CAMERACONTROLLERMOVEFORWARD_H

#include "../../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../../../Expedition Engine/Camera/Camera.h"
#include "../../../../Expedition Engine/Scenes/SceneManager.h"

#include <stdio.h>

class CameraControllerMoveForward : public KeyboardInputComponent
{

private:

	void OnKeyPressed() override
	{
	}

	void OnKeyHeld() override
	{
		SceneManager::GetCurrentPerspectiveCamera()->TranslateFwdBack(3);
		SceneManager::GetCurrentPerspectiveCamera()->Update();
	}
	void OnKeyReleased() override
	{

	}

};

#endif // !CAMERACONTROLLERMOVEFORWARD_H
#ifndef CAMERACONTROLLERMOVEBACKWARD_H
#define CAMERACONTROLLERMOVEBACKWARD_H

#include "../../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../../../Expedition Engine/Scenes/SceneManager.h"
#include "../../../../Expedition Engine/Camera/Camera.h"
#include "../../../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"

#include <stdio.h>

class CameraControllerMoveBackward : public KeyboardInputComponent
{

private:

	void OnKeyPressed() override
	{
	}

	void OnKeyHeld() override
	{
		SceneManager::GetCurrentPerspectiveCamera()->TranslateFwdBack(-3);
		SceneManager::GetCurrentPerspectiveCamera()->Update();
	}
	void OnKeyReleased() override
	{

	}

};

#endif // !CAMERACONTROLLERMOVEBASCKWARD_H
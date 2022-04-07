#ifndef CAMERACONTROLLERTILTDOWN_H
#define CAMERACONTROLLERTILTDOWN_H

#include "../../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../../../Expedition Engine/Scenes/SceneManager.h"
#include "../../../../Expedition Engine/Camera/Camera.h"
#include <stdio.h>

class CameraControllerTiltDown : public KeyboardInputComponent
{

private:

	void OnKeyPressed() override
	{
	}

	void OnKeyHeld() override
	{
		SceneManager::GetCurrentPerspectiveCamera()->TiltUpDown(-.02f);
		SceneManager::GetCurrentPerspectiveCamera()->Update();
	}
	void OnKeyReleased() override
	{

	}

};

#endif // !CAMERACONTROLLERTILTDOWN_H
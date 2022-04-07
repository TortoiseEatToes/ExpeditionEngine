#ifndef CAMERACONTROLLERMOVERIGHT_H
#define CAMERACONTROLLERMOVERIGHT_H

#include "../../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../../../Expedition Engine/Scenes/SceneManager.h"
#include "../../../../Expedition Engine/Camera/Camera.h"

#include <stdio.h>

class CameraControllerMoveRight : public KeyboardInputComponent
{

private:

	void OnKeyPressed() override
	{
	}

	void OnKeyHeld() override
	{
		SceneManager::GetCurrentPerspectiveCamera()->TranslateLeftRight(1);
		SceneManager::GetCurrentPerspectiveCamera()->Update();
	}
	void OnKeyReleased() override
	{

	}	

};

#endif // !CAMERACONTROLLERMOVERIGHT_H
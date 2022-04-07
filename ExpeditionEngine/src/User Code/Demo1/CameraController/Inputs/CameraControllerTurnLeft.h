#ifndef CAMERACONTROLLERTURNLEFT_H
#define CAMERACONTROLLERTURNLEFT_H

#include "../../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../../../Expedition Engine/Scenes/SceneManager.h"
#include "../../../../Expedition Engine/Camera/Camera.h"


#include <stdio.h>

class CameraControllerTurnLeft : public KeyboardInputComponent
{

private:

	void OnKeyPressed() override
	{
	}

	void OnKeyHeld() override
	{
		SceneManager::GetCurrentPerspectiveCamera()->TurnLeftRight(.02f);
		SceneManager::GetCurrentPerspectiveCamera()->Update();
	}
	void OnKeyReleased() override
	{

	}

};

#endif // !CAMERACONTROLLERTURNLEFT_H
#ifndef CAMERACONTROLLERMOVELEFT_H
#define CAMERACONTROLLERMOVELEFT_H

#include "../../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../../../Expedition Engine/GraphicsScene/GraphicsScene.h"
#include "../../../../Expedition Engine/Camera/Camera.h"

#include <stdio.h>

class CameraControllerMoveLeft : public KeyboardInputComponent
{

private:

	void OnKeyPressed() override
	{
	}

	void OnKeyHeld() override
	{
		SceneManager::GetCurrentPerspectiveCamera()->TranslateLeftRight(-1);
		SceneManager::GetCurrentPerspectiveCamera()->Update();

	}
	void OnKeyReleased() override
	{

	}

};

#endif // !CAMERACONTROLLERMOVELEFT_H
#include "CameraController.h"


CameraController::CameraController(const SceneName& sceneToExistIn)
	: GameObject(sceneToExistIn)
{

}

void CameraController::OnSceneEnter() {
	cameraMoveBackward.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyK);
	cameraMoveForward.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyI);
	cameraMoveLeft.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyJ);
	cameraMoveRight.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyL);
	cameraTurnRight.RegisterForOnHeld(GetRegisteredScene(), Input::ArrowRight);
	cameraTurnLeft.RegisterForOnHeld(GetRegisteredScene(), Input::ArrowLeft);
	cameraTiltUp.RegisterForOnHeld(GetRegisteredScene(), Input::ArrowUp);
	cameraTiltDown.RegisterForOnHeld(GetRegisteredScene(), Input::ArrowDown);
}

void CameraController::OnSceneExit() {
	cameraMoveBackward.DeregisterFromOnHeld();
	cameraMoveForward.DeregisterFromOnHeld();
	cameraMoveLeft.DeregisterFromOnHeld();
	cameraMoveRight.DeregisterFromOnHeld();
	cameraTurnRight.DeregisterFromOnHeld();
	cameraTurnLeft.DeregisterFromOnHeld();
	cameraTiltUp.DeregisterFromOnHeld();
	cameraTiltDown.DeregisterFromOnHeld();
}

void CameraController::ActiveTerrainAlignment(Camera* inCam, TerrainModel* inTerrain, int inOffset)
{
	cameraTerrainAligner.StartUpdating(this->GetRegisteredScene());

	cameraTerrainAligner.cam = inCam;
	cameraTerrainAligner.terrain = inTerrain;
	cameraTerrainAligner.offset = static_cast<float>(inOffset);

}

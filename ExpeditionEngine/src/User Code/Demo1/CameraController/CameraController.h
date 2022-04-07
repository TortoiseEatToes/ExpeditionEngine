#pragma once

#include "../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "Inputs/CameraInputInclude.h"

#include "CameraToTerrainAligner.h"

class TerrainModel;
class Camera;

class CameraController : public GameObject
{
public:
	CameraController() = delete;
	CameraController(const SceneName& startingScene);
	CameraController(CameraController&& other) = delete;
	CameraController(const CameraController& other) = delete;
	CameraController& operator= (CameraController&& other) = delete;
	CameraController& operator= (const CameraController& other) = delete;
	~CameraController() {};

	void OnSceneEnter() override;
	void OnSceneExit() override;

	void ActiveTerrainAlignment(Camera* inCam, TerrainModel* inTerrain, int inOffset);

private:
	CameraControllerMoveBackward cameraMoveBackward;
	CameraControllerMoveForward cameraMoveForward;
	CameraControllerMoveLeft cameraMoveLeft;
	CameraControllerMoveRight cameraMoveRight;
	CameraControllerTurnRight cameraTurnRight;
	CameraControllerTurnLeft cameraTurnLeft;
	CameraControllerTiltUp cameraTiltUp;
	CameraControllerTiltDown cameraTiltDown;

	CameraToTerrainAligner cameraTerrainAligner;
};


#pragma once

#include "Input_CameraFwdBack.h"
#include "Input_CameraLeftRight.h"
#include "Update_Camera.h"
#include "Input_Sprint.h"
#include "Input_FlashLight.h"

#include "../../Expedition Engine/Scene Components/Game Object/GameObject.h"

class TerrainModel;
class Camera;

class Forest_Camera : public GameObject
{
public:

	Forest_Camera() = delete;
	Forest_Camera(Forest_Camera&&) = delete;
	Forest_Camera(const Forest_Camera&) = delete;
	const Forest_Camera& operator =(Forest_Camera&&) = delete;
	const Forest_Camera& operator =(const Forest_Camera&) = delete;

	Forest_Camera(SceneName sceneName);
	~Forest_Camera();

	float GetSpeed() const;
	void SetSpeed(const float& inSpeed);

	void SetTerrainAlignInfo(TerrainModel* inTerrain, Camera* cam, const float& offset);

	void OnSceneEnter() override;
	void OnSceneExit() override;

private:
	
	Input_CameraFwdBack camFwd;
	Input_CameraFwdBack camBack;
	Input_CameraLeftRight camLeft;
	Input_CameraLeftRight camRight;

	Input_Sprint inputSprint;
	Input_FlashLight inputFlash;

	Update_Camera camUpdate;

	float currentSpeed;
	float walkSpeed = 2;
	float sprintSpeed = 4;
	

};
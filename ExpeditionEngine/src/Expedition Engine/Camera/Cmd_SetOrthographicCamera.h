#pragma once

#include "CameraManagerCommand.h"

class Camera;

class Cmd_SetOrthographicCamera : public CameraManagerCommand
{
public:
	Cmd_SetOrthographicCamera() = default;
	Cmd_SetOrthographicCamera(const Cmd_SetOrthographicCamera& other) = delete;
	Cmd_SetOrthographicCamera& operator= (const Cmd_SetOrthographicCamera& other) = delete;
	~Cmd_SetOrthographicCamera() = default;

	void Initialize(Camera * const pInitCamera);

	virtual void Execute(CameraManager * const pCameraManager) override;
	virtual void RecycleCommand(CameraManager * const pCameraManager) override;

private:
	Camera* pCamera;
};
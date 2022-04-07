#pragma once

#include "CameraManagerCommand.h"

class Camera;

class Cmd_SetPerspectiveCamera : public CameraManagerCommand
{
public:
	Cmd_SetPerspectiveCamera() = default;
	Cmd_SetPerspectiveCamera(const Cmd_SetPerspectiveCamera& other) = delete;
	Cmd_SetPerspectiveCamera& operator= (const Cmd_SetPerspectiveCamera& other) = delete;
	~Cmd_SetPerspectiveCamera() = default;

	void Initialize(Camera * const pInitCamera);

	virtual void Execute(CameraManager * const pCameraManager) override;
	virtual void RecycleCommand(CameraManager * const pCameraManager) override;

private:
	Camera* pCamera;
};
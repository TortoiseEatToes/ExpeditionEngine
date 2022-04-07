#pragma once

class CameraManager;

class CameraManagerCommand
{
public:
	CameraManagerCommand() = default;
	CameraManagerCommand(const CameraManagerCommand& other) = delete;
	CameraManagerCommand& operator= (const CameraManagerCommand& other) = delete;
	virtual ~CameraManagerCommand() = default;

	virtual void Execute(CameraManager * const pCameraManager) = 0;
	virtual void RecycleCommand(CameraManager * const pCameraManager) = 0;
};
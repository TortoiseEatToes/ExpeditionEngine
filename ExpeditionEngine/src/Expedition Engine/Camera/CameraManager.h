#pragma once

#include "CameraDataManagerAttorney.h"
#include "../Containers/Pool.h"
#include "../Containers/Queue.h"

#include "Cmd_SetOrthographicCamera.h"
#include "Cmd_SetPerspectiveCamera.h"

class Camera;
class CameraManagerCommand;
enum SceneName;

class CameraManager
{
public:
	CameraManager() = default;
	CameraManager(const CameraManager& other) = delete;
	CameraManager& operator= (const CameraManager& other) = delete;
	~CameraManager() = default;

	void Initialize(const SceneName& sceneName);

	void AcquireCameraData(Camera * const pCamera);
	void ReleaseCameraData(Camera * const pCamera);

	void SetPerspectiveCamera(Camera * const pCamera);
	void SetOrthographicCamera(Camera * const pCamera);

	Camera * const GetPerspectiveCamera();
	Camera * const GetOrthographicCamera();

	void Synchronize();

	void ShutDown();

	const CameraDataManager& GetCameraDataManager() const;

private:
	friend class CameraManagerAttorney;

	void CmdCall_SetOrthographicCamera(Camera * const pCamera);
	void CmdCall_SetPerspectiveCamera(Camera * const pCamera);

	void CmdCall_RecycleCommand(const Cmd_SetOrthographicCamera * pCommand);
	void CmdCall_RecycleCommand(const Cmd_SetPerspectiveCamera * pCommand);

	CameraDataManager cameraDataManager;
	Pool<Cmd_SetOrthographicCamera> poolCmd_SetOrthographicCamera;
	Pool<Cmd_SetPerspectiveCamera> poolCmd_SetPerspectiveCamera;
	Queue<CameraManagerCommand*> commandQueue;
	Camera* pCurrentOrthographicCamera;
	Camera* pCurrentPerspectiveCamera;
};
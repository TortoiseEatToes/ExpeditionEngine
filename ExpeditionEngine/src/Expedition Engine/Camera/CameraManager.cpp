#include "CameraManager.h"

#include "CameraManagerCommand.h"

#include "Camera.h"

#include "../Math/Vector/Vector4F.h"
#include "../Engine/ExpeditionEngine.h"
#include "../../Expedition Resources/LayerSettings.h"

void CameraManager::Initialize(const SceneName& sceneName)
{
	//-------------------------- Initialize Orthographic Camera -------------------------------------------------
	pCurrentOrthographicCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D, sceneName);
	pCurrentOrthographicCamera->SetOrthographic(0, ExpeditionEngine::GetWidth(), 0, ExpeditionEngine::GetHeight(), 0, static_cast<float>(NumberOfLayers));

	Vector4F up2DCam(0.0f, 1.0f, 0.0f);
	Vector4F pos2DCam(0.0f, 0.0f, 0.0f, 1);
	Vector4F lookAt2DCam(0.0f, 0.0f, 1.0f);
	pCurrentOrthographicCamera->SetOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);
	pCurrentOrthographicCamera->Update();  // Note: if the camera moves/changes, we need to call update again

	CameraDataManagerAttorney::CameraManagerControls::SetOrthographicCamera(cameraDataManager, pCurrentOrthographicCamera);

	//-------------------------- Initialize Perspective Camera -------------------------------------------------
	pCurrentPerspectiveCamera = new Camera(Camera::Type::PERSPECTIVE_3D, sceneName);
	pCurrentPerspectiveCamera->SetPerspective(3.1415926f / 3, float(ExpeditionEngine::GetWidth()) / float(ExpeditionEngine::GetHeight()), 1.0f, 20000.0f);

	// Orient Camera
	Vector4F up3DCam(0.0f, 1.0f, 0.0f);
	Vector4F pos3DCam(0, 50, 200, 1);
	Vector4F lookAt3DCam(0.0f, 0.0f, 0.0f);
	pCurrentPerspectiveCamera->SetOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	pCurrentPerspectiveCamera->Update();  // Note: if the camera moves/changes, we need to call update again

	CameraDataManagerAttorney::CameraManagerControls::SetPerspectiveCamera(cameraDataManager, pCurrentPerspectiveCamera);
}

void CameraManager::AcquireCameraData(Camera * const pCamera)
{
	CameraDataManagerAttorney::CameraManagerControls::AcquireCameraData(cameraDataManager, pCamera);
}

void CameraManager::ReleaseCameraData(Camera * const pCamera)
{
	CameraDataManagerAttorney::CameraManagerControls::ReleaseCameraData(cameraDataManager, pCamera);
}

void CameraManager::SetPerspectiveCamera(Camera * const pCamera)
{
	Cmd_SetOrthographicCamera* pCommand = poolCmd_SetOrthographicCamera.GetPooledObject();
	pCommand->Initialize(pCamera);
	commandQueue.Push(pCommand);
}

void CameraManager::SetOrthographicCamera(Camera * const pCamera)
{
	Cmd_SetPerspectiveCamera* pCommand = poolCmd_SetPerspectiveCamera.GetPooledObject();
	pCommand->Initialize(pCamera);
	commandQueue.Push(pCommand);
}

Camera * const CameraManager::GetPerspectiveCamera()
{
	return pCurrentPerspectiveCamera;
}

Camera * const CameraManager::GetOrthographicCamera()
{
	return pCurrentOrthographicCamera;
}

void CameraManager::Synchronize()
{
	while (commandQueue.GetSize() > 0)
	{
		CameraManagerCommand* pCurrentCommand = commandQueue.Pop();
		pCurrentCommand->Execute(this);
		pCurrentCommand->RecycleCommand(this);
	}
	CameraDataManagerAttorney::CameraManagerControls::Synchronize(cameraDataManager);
}

void CameraManager::ShutDown()
{
	delete pCurrentOrthographicCamera;
	delete pCurrentPerspectiveCamera;
}

const CameraDataManager & CameraManager::GetCameraDataManager() const
{
	return cameraDataManager;
}

void CameraManager::CmdCall_SetOrthographicCamera(Camera * const pCamera)
{
	pCurrentOrthographicCamera = pCamera;
	CameraDataManagerAttorney::CameraManagerControls::SetOrthographicCamera(cameraDataManager, pCamera);
}

void CameraManager::CmdCall_SetPerspectiveCamera(Camera * const pCamera)
{
	pCurrentPerspectiveCamera = pCamera;
	CameraDataManagerAttorney::CameraManagerControls::SetPerspectiveCamera(cameraDataManager, pCamera);
}

void CameraManager::CmdCall_RecycleCommand(const Cmd_SetOrthographicCamera * pCommand)
{
	poolCmd_SetOrthographicCamera.RecycleObject(pCommand);
}

void CameraManager::CmdCall_RecycleCommand(const Cmd_SetPerspectiveCamera * pCommand)
{
	poolCmd_SetPerspectiveCamera.RecycleObject(pCommand);
}

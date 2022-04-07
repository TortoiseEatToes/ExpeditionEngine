#include "Cmd_SetOrthographicCamera.h"

#include "CameraManagerAttorney.h"

void Cmd_SetOrthographicCamera::Initialize(Camera * const pInitCamera)
{
	pCamera = pInitCamera;
}

void Cmd_SetOrthographicCamera::Execute(CameraManager * const pCameraManager)
{
	CameraManagerAttorney::CommandControls::CmdCall_SetOrthographicCamera(pCameraManager, pCamera);
}

void Cmd_SetOrthographicCamera::RecycleCommand(CameraManager * const pCameraManager)
{
	CameraManagerAttorney::CommandControls::CmdCall_RecycleCommand(pCameraManager, this);
}
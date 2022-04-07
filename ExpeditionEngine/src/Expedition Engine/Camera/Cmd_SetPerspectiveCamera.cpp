#include "Cmd_SetPerspectiveCamera.h"

#include "CameraManagerAttorney.h"

void Cmd_SetPerspectiveCamera::Initialize(Camera * const pInitCamera)
{
	pCamera = pInitCamera;
}

void Cmd_SetPerspectiveCamera::Execute(CameraManager * const pCameraManager)
{
	CameraManagerAttorney::CommandControls::CmdCall_SetPerspectiveCamera(pCameraManager, pCamera);
}

void Cmd_SetPerspectiveCamera::RecycleCommand(CameraManager * const pCameraManager)
{
	CameraManagerAttorney::CommandControls::CmdCall_RecycleCommand(pCameraManager, this);
}
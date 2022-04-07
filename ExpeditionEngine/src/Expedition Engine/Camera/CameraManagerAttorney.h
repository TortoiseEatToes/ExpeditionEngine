#pragma once

#include "CameraManager.h"

class CameraManagerAttorney
{
public:
	class CommandControls
	{
	private:
		friend class Cmd_SetPerspectiveCamera;
		friend class Cmd_SetOrthographicCamera;

		static void CmdCall_SetOrthographicCamera(CameraManager * const pCameraManager, Camera * const pCamera)
		{
			pCameraManager->CmdCall_SetOrthographicCamera(pCamera);
		}
		static void CmdCall_SetPerspectiveCamera(CameraManager * const pCameraManager, Camera * const pCamera)
		{
			pCameraManager->CmdCall_SetPerspectiveCamera(pCamera);
		}


		static void CmdCall_RecycleCommand(CameraManager * const pCameraManager, Cmd_SetOrthographicCamera * const pCommand)
		{
			pCameraManager->CmdCall_RecycleCommand(pCommand);
		}
		static void CmdCall_RecycleCommand(CameraManager * const pCameraManager, Cmd_SetPerspectiveCamera * const pCommand)
		{
			pCameraManager->CmdCall_RecycleCommand(pCommand);
		}

	};
};
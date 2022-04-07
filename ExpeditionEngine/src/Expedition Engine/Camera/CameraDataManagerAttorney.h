#pragma once

#include "CameraDataManager.h"

class CameraDataManagerAttorney
{
public:
	class CameraManagerControls
	{
	private:
		friend class CameraManager;

		static void Synchronize(CameraDataManager& cameraDataManager)
		{
			cameraDataManager.Synchronize();
		}

		static void SetOrthographicCamera(CameraDataManager& cameraDataManager, Camera * const pCamera)
		{
			cameraDataManager.SetOrthographicCamera(pCamera);
		}

		static void SetPerspectiveCamera(CameraDataManager& cameraDataManager, Camera * const pCamera)
		{
			cameraDataManager.SetPerspectiveCamera(pCamera);
		}

		static void AcquireCameraData(CameraDataManager& cameraDataManager, Camera * const pCamera)
		{
			cameraDataManager.AcquireCameraData(pCamera);
		}
		static void ReleaseCameraData(CameraDataManager& cameraDataManager, Camera * const pCamera)
		{
			cameraDataManager.ReleaseCameraData(pCamera);
		}
	};
};
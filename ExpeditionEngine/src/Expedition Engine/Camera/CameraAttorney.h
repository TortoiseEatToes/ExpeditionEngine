#pragma once

#include "Camera.h"

class CameraAttorney
{
public:
	class CameraDataManagerControls
	{
	private:
		friend class CameraDataManager;

		static PooledResourceIterator<CameraDataDoubleBuffer>& GetIterator(Camera * const pCamera)
		{
			return pCamera->GetIterator();
		}
	};
};
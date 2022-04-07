#include "CameraDataManager.h"

#include "CameraDataDoubleBufferAttorney.h"
#include "CameraAttorney.h"

CameraDataManager::CameraDataManager()
	:doubleBufferPool(2)
{
}

const CameraData & CameraDataManager::GetCurrentCameraDataOrthograpic() const
{
	return pCurrentOrthographicCamera->GetObserverBuffer();
}

const CameraData & CameraDataManager::GetCurrentCameraDataPerspective() const
{
	return pCurrentPerspectiveCamera->GetObserverBuffer();
}

void CameraDataManager::AcquireCameraData(Camera * const pCamera)
{
	doubleBufferPool.AcquireResource(CameraAttorney::CameraDataManagerControls::GetIterator(pCamera));
	activeDoubleBuffers.PushBack(CameraAttorney::CameraDataManagerControls::GetIterator(pCamera));
}

void CameraDataManager::ReleaseCameraData(Camera * const pCamera)
{
	activeDoubleBuffers.Remove(CameraAttorney::CameraDataManagerControls::GetIterator(pCamera));
	doubleBufferPool.ReleaseResource(CameraAttorney::CameraDataManagerControls::GetIterator(pCamera));
}

void CameraDataManager::Synchronize()
{
	activeDoubleBuffers.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		CameraDataDoubleBufferAttorney::ManagerControl::Synchronize(currentIterator.GetCurrentObject());
		++currentIterator;
	}
}

void CameraDataManager::SetOrthographicCamera(Camera * const pCamera)
{
	pCurrentOrthographicCamera = &CameraAttorney::CameraDataManagerControls::GetIterator(pCamera).GetCurrentObject();
}

void CameraDataManager::SetPerspectiveCamera(Camera * const pCamera)
{
	pCurrentPerspectiveCamera = &CameraAttorney::CameraDataManagerControls::GetIterator(pCamera).GetCurrentObject();
}

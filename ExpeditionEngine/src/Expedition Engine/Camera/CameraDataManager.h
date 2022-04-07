#pragma once

#include "../Containers/ResourcePool.h"
#include "../Containers/List_PooledResource.h"
#include "CameraDataDoubleBuffer.h"

class Camera;
class CameraData;

class CameraDataManager
{
public:
	CameraDataManager();
	CameraDataManager(const CameraDataManager& other) = delete;
	CameraDataManager& operator= (const CameraDataManager& other) = delete;
	~CameraDataManager() = default;

	const CameraData& GetCurrentCameraDataOrthograpic() const;
	const CameraData& GetCurrentCameraDataPerspective() const;


private:
	friend class CameraDataManagerAttorney;

	void AcquireCameraData(Camera * const pCamera);
	void ReleaseCameraData(Camera * const pCamera);

	//Camera Manager Calls
	void Synchronize();
	void SetOrthographicCamera(Camera * const pCamera);
	void SetPerspectiveCamera(Camera * const pCamera);

	ResourcePool<CameraDataDoubleBuffer> doubleBufferPool;
	List_PooledResource<CameraDataDoubleBuffer> activeDoubleBuffers;
	PooledResourceIterator<CameraDataDoubleBuffer> currentIterator;

	const CameraDataDoubleBuffer* pCurrentOrthographicCamera;
	const CameraDataDoubleBuffer* pCurrentPerspectiveCamera;
};
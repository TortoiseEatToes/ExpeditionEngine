#pragma once

#include "Matrix4FDoubleBufferManager.h"
#include "Vector4FDoubleBufferManager.h"
#include "MaterialManager.h"
#include "PointerDoubleBufferManager.h"

class GraphicsResourcesManager
{
public:
	GraphicsResourcesManager()
	{
	}
	GraphicsResourcesManager(const GraphicsResourcesManager&) = delete;
	GraphicsResourcesManager& operator= (const GraphicsResourcesManager&) = delete;
	~GraphicsResourcesManager()
	{
	};

	//------------------------------- Acquire Resource -----------------------------------------
	//Acquire a double buffer from a pool
	void AcquireDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);
	void AcquireDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);
	void AcquireMaterial(Material*& pOutMaterial);
	void AcquirePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator);

	//------------------------------- Release Resource -----------------------------------------
	//Release a double buffer back into it's pool
	void ReleaseDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);
	void ReleaseDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);
	void ReleaseMaterial(Material*& pBufferToRelease);
	void ReleasePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator);

	//------------------------------- Register Synchronization -----------------------------------------
	//These functions are used to register a double buffer for synchronization in it's corresponding manager.
	void RegisterForSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);
	void RegisterForSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);
	void RegisterForSynchronization(Material*& pBufferToSynchronize);
	void RegisterForSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator);

	//------------------------------- Deregister Synchronization -----------------------------------------
	//These functions are used to deregister a double buffer from synchronization from it's corresponding manager.
	void DeregisterFromSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);
	void DeregisterFromSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);
	void DeregisterFromSynchronization(Material*& pBufferToNoLongerSynchronize);
	void DeregisterFromSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator);

	//-------------------------------- Synchronize ------------------------------------------------
	/// <summary>Call synchronize on all of the double buffer managers.</summary>
	void Synchronize();

private:
	Matrix4FDoubleBufferManager matrix4FDoubleBufferManager;
	Vector4FDoubleBufferManager vector4FDoubleBufferManager;
	MaterialManager materialManager;
	PointerDoubleBufferManager pointerDoubleBufferManager;
};
#pragma once
#include "PointerDoubleBuffer.h"

#include "../../Containers/ResourcePool.h"
#include "../../Containers/List_PooledResource.h"

class PointerDoubleBufferManager
{
public:
	PointerDoubleBufferManager();
	PointerDoubleBufferManager(const PointerDoubleBufferManager&) = delete;
	PointerDoubleBufferManager& operator= (const PointerDoubleBufferManager&) = delete;
	~PointerDoubleBufferManager() = default;

	void AcquirePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator);
	void ReleasePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator);

	void RegisterForSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator);
	void DeregisterFromSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator);

	void Synchronize();

private:
	friend class PointerDoubleBufferManagerAttorney;

	ResourcePool<PointerDoubleBuffer> doubleBufferPool;
	List_PooledResource<PointerDoubleBuffer> activeDoubleBuffers;
	PooledResourceIterator<PointerDoubleBuffer> currentIterator;
};
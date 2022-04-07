#pragma once

#pragma once

#include "../../Containers/ResourcePool.h"
#include "../../Containers/List_PooledResource.h"

#include "Vector4FDoubleBuffer.h"

class Vector4FDoubleBufferManager
{
public:
	Vector4FDoubleBufferManager();
	Vector4FDoubleBufferManager(const Vector4FDoubleBufferManager&) = delete;
	Vector4FDoubleBufferManager& operator= (const Vector4FDoubleBufferManager&) = delete;
	~Vector4FDoubleBufferManager() = default;

	void AcquireDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);
	void ReleaseDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);
	void RegisterForSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);
	void DeregisterFromSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator);

	void Synchronize();

private:
	friend class Vector4FDoubleBufferManagerAttorney;

	ResourcePool<Vector4FDoubleBuffer> doubleBufferPool;
	List_PooledResource<Vector4FDoubleBuffer> activeDoubleBuffers;
	PooledResourceIterator<Vector4FDoubleBuffer> currentIterator;
};
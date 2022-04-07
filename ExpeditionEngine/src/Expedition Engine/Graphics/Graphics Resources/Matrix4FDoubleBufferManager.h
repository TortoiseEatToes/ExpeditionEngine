#pragma once

#include "../../Containers/ResourcePool.h"
#include "../../Containers/List_PooledResource.h"

#include "Matrix4FDoubleBuffer.h"

class Matrix4FDoubleBufferManager
{
public:
	Matrix4FDoubleBufferManager();
	Matrix4FDoubleBufferManager(const Matrix4FDoubleBufferManager&) = delete;
	Matrix4FDoubleBufferManager& operator= (const Matrix4FDoubleBufferManager&) = delete;
	~Matrix4FDoubleBufferManager() = default;

	void AcquireDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);
	void ReleaseDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);

	void RegisterForSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);
	void DeregisterFromSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator);

	void Synchronize();

private:
	friend class Matrix4FDoubleBufferManagerAttorney;

	ResourcePool<Matrix4FDoubleBuffer> doubleBufferPool;
	List_PooledResource<Matrix4FDoubleBuffer> activeDoubleBuffers;
	PooledResourceIterator<Matrix4FDoubleBuffer> currentIterator;
};
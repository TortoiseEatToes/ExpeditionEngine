#include "Matrix4FDoubleBufferManager.h"

#include "Matrix4FDoubleBufferAttorney.h"

#include "../../../Expedition Resources/GraphicsResourcesSettings.h"

Matrix4FDoubleBufferManager::Matrix4FDoubleBufferManager()
	:doubleBufferPool(NumberOfMatrix4FDoubleBuffers)
{
}

void Matrix4FDoubleBufferManager::AcquireDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	doubleBufferPool.AcquireResource(iterator);
}

void Matrix4FDoubleBufferManager::ReleaseDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	doubleBufferPool.ReleaseResource(iterator);
}

void Matrix4FDoubleBufferManager::RegisterForSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	activeDoubleBuffers.PushBack(iterator);
}

void Matrix4FDoubleBufferManager::DeregisterFromSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	activeDoubleBuffers.Remove(iterator);
}

void Matrix4FDoubleBufferManager::Synchronize()
{
	activeDoubleBuffers.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		Matrix4FDoubleBufferAttorney::ManagerControl::Synchronize(currentIterator.GetCurrentObject());
		++currentIterator;
	}
}
#include "Vector4FDoubleBufferManager.h"

#include "Vector4FDoubleBufferAttorney.h"

#include "../../../Expedition Resources/GraphicsResourcesSettings.h"

Vector4FDoubleBufferManager::Vector4FDoubleBufferManager()
	:doubleBufferPool(NumberOfVector4FDoubleBuffers)
{
}

void Vector4FDoubleBufferManager::AcquireDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	doubleBufferPool.AcquireResource(iterator);
}

void Vector4FDoubleBufferManager::ReleaseDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	doubleBufferPool.ReleaseResource(iterator);
}

void Vector4FDoubleBufferManager::RegisterForSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	activeDoubleBuffers.PushBack(iterator);
}

void Vector4FDoubleBufferManager::DeregisterFromSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	activeDoubleBuffers.Remove(iterator);
}

void Vector4FDoubleBufferManager::Synchronize()
{
	activeDoubleBuffers.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		Vector4FDoubleBufferAttorney::ManagerControl::Synchronize(currentIterator.GetCurrentObject());
		++currentIterator;
	}
}
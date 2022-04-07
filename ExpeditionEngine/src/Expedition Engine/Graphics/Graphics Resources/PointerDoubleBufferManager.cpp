#include "PointerDoubleBufferManager.h"

#include "PointerDoubleBufferAttorney.h"

#include "../../../Expedition Resources/GraphicsResourcesSettings.h"

PointerDoubleBufferManager::PointerDoubleBufferManager()
	:doubleBufferPool(NumberOfPointerDoubleBuffers)
{
}

void PointerDoubleBufferManager::AcquirePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	doubleBufferPool.AcquireResource(iterator);
}

void PointerDoubleBufferManager::ReleasePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	doubleBufferPool.ReleaseResource(iterator);
}

void PointerDoubleBufferManager::RegisterForSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	activeDoubleBuffers.PushBack(iterator);
}

void PointerDoubleBufferManager::DeregisterFromSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	activeDoubleBuffers.Remove(iterator);
}

void PointerDoubleBufferManager::Synchronize()
{
	activeDoubleBuffers.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		PointerDoubleBufferAttorney::ManagerControl::Synchronize(currentIterator.GetCurrentObject());
		++currentIterator;
	}
}
#include "GraphicsResourcesManager.h"

void GraphicsResourcesManager::AcquireDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	matrix4FDoubleBufferManager.AcquireDoubleBuffer(iterator);
}

void GraphicsResourcesManager::AcquireDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	vector4FDoubleBufferManager.AcquireDoubleBuffer(iterator);
}

void GraphicsResourcesManager::AcquireMaterial(Material*& pOutMaterial)
{
	materialManager.AcquireMaterial(vector4FDoubleBufferManager, pOutMaterial);
}

void GraphicsResourcesManager::AcquirePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	pointerDoubleBufferManager.AcquirePointer(iterator);
}

void GraphicsResourcesManager::ReleaseDoubleBuffer(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	matrix4FDoubleBufferManager.ReleaseDoubleBuffer(iterator);
}

void GraphicsResourcesManager::ReleaseDoubleBuffer(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	vector4FDoubleBufferManager.ReleaseDoubleBuffer(iterator);
}

void GraphicsResourcesManager::ReleaseMaterial(Material*& pBufferToRelease)
{
	materialManager.ReleaseMaterial(vector4FDoubleBufferManager, pBufferToRelease);
}

void GraphicsResourcesManager::ReleasePointer(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	pointerDoubleBufferManager.ReleasePointer(iterator);
}

void GraphicsResourcesManager::RegisterForSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	matrix4FDoubleBufferManager.RegisterForSynchronization(iterator);
}

void GraphicsResourcesManager::RegisterForSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	vector4FDoubleBufferManager.RegisterForSynchronization(iterator);
}

void GraphicsResourcesManager::RegisterForSynchronization(Material*& pBufferToSynchronize)
{
	materialManager.RegisterForSynchronization(vector4FDoubleBufferManager, pBufferToSynchronize);
}

void GraphicsResourcesManager::RegisterForSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	pointerDoubleBufferManager.RegisterForSynchronization(iterator);
}

void GraphicsResourcesManager::DeregisterFromSynchronization(PooledResourceIterator<Matrix4FDoubleBuffer>& iterator)
{
	matrix4FDoubleBufferManager.DeregisterFromSynchronization(iterator);
}

void GraphicsResourcesManager::DeregisterFromSynchronization(PooledResourceIterator<Vector4FDoubleBuffer>& iterator)
{
	vector4FDoubleBufferManager.DeregisterFromSynchronization(iterator);
}

void GraphicsResourcesManager::DeregisterFromSynchronization(Material*& pBufferToNoLongerSynchronize)
{
	materialManager.DeregisterFromSynchronization(vector4FDoubleBufferManager, pBufferToNoLongerSynchronize);
}

void GraphicsResourcesManager::DeregisterFromSynchronization(PooledResourceIterator<PointerDoubleBuffer>& iterator)
{
	pointerDoubleBufferManager.DeregisterFromSynchronization(iterator);
}

void GraphicsResourcesManager::Synchronize()
{
	matrix4FDoubleBufferManager.Synchronize();
	vector4FDoubleBufferManager.Synchronize();
	pointerDoubleBufferManager.Synchronize();
}

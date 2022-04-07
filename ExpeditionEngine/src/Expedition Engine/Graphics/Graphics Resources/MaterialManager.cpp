#include "MaterialManager.h"

#include "MaterialAttorney.h"

void MaterialManager::AcquireMaterial(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pOutMaterial)
{
	pOutMaterial = materialPool.GetPooledObject();
	MaterialAttorney::ManagerControl::AcquireBuffers(vector4FDoubleBufferManager, pOutMaterial);
}

void MaterialManager::ReleaseMaterial(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pBufferToRelease)
{
	MaterialAttorney::ManagerControl::ReleaseBuffers(vector4FDoubleBufferManager, pBufferToRelease);
	materialPool.RecycleObject(pBufferToRelease);
}

void MaterialManager::RegisterForSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pBufferToSynchronize)
{
	MaterialAttorney::ManagerControl::RegisterForSynchronization(vector4FDoubleBufferManager, pBufferToSynchronize);
}

void MaterialManager::DeregisterFromSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pBufferToNoLongerSynchronize)
{
	MaterialAttorney::ManagerControl::DeregisterFromSynchronization(vector4FDoubleBufferManager, pBufferToNoLongerSynchronize);
}

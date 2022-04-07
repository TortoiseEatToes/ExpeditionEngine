#pragma once
#include "../../Containers/Pool.h"
#include "../../Containers/List.h"

#include "Material.h"

class MaterialManager
{
public:
	MaterialManager() = default;
	MaterialManager(const MaterialManager&) = delete;
	MaterialManager& operator= (const MaterialManager&) = delete;
	~MaterialManager() = default;

	void AcquireMaterial(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pOutMaterial);
	void ReleaseMaterial(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pBufferToRelease);

	void RegisterForSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pBufferToSynchronize);
	void DeregisterFromSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& pBufferToNoLongerSynchronize);

private:
	friend class MaterialManagerAttorney;

	Pool<Material> materialPool;
};
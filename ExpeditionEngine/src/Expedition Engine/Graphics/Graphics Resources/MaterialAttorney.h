#pragma once

#include "Material.h"


class MaterialAttorney
{
public:
	class ManagerControl
	{
	private:
		friend class MaterialManager;

		static void AcquireBuffers(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& material)
		{
			material->AcquireBuffers(vector4FDoubleBufferManager);
		}

		static void ReleaseBuffers(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& material)
		{
			material->ReleaseBuffers(vector4FDoubleBufferManager);
		}

		static void RegisterForSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& material)
		{
			material->RegisterForSynchronization(vector4FDoubleBufferManager);
		}

		static void DeregisterFromSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager, Material*& material)
		{
			material->DeregisterFromSynchronization(vector4FDoubleBufferManager);
		}
	};
};
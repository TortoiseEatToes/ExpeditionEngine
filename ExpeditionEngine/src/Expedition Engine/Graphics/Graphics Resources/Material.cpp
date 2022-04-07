#include "Material.h"
#include "Vector4FDoubleBufferManager.h"
#include "Vector4FDoubleBufferAttorney.h"

Vector4FDoubleBuffer& Material::Ambient()
{
	return ambient.GetCurrentObject();
}

Vector4FDoubleBuffer& Material::Diffuse()
{
	return diffuse.GetCurrentObject();
}

Vector4FDoubleBuffer& Material::Specular()
{
	return specular.GetCurrentObject();
}

void Material::Initialize(const Vector4F& startingValues)
{
	ambient.GetCurrentObject().Initialize(startingValues);
	diffuse.GetCurrentObject().Initialize(startingValues);
	specular.GetCurrentObject().Initialize(startingValues);
}

void Material::Initialize(const Vector4F& startingAmbient, const Vector4F& startingDiffuse, const Vector4F& startingSpecular)
{
	ambient.GetCurrentObject().Initialize(startingAmbient);
	diffuse.GetCurrentObject().Initialize(startingDiffuse);
	specular.GetCurrentObject().Initialize(startingSpecular);
}

void Material::AcquireBuffers(Vector4FDoubleBufferManager& vector4FDoubleBufferManager)
{
	vector4FDoubleBufferManager.AcquireDoubleBuffer(ambient);
	vector4FDoubleBufferManager.AcquireDoubleBuffer(diffuse);
	vector4FDoubleBufferManager.AcquireDoubleBuffer(specular);
}

void Material::ReleaseBuffers(Vector4FDoubleBufferManager& vector4FDoubleBufferManager)
{
	vector4FDoubleBufferManager.ReleaseDoubleBuffer(ambient);
	vector4FDoubleBufferManager.ReleaseDoubleBuffer(diffuse);
	vector4FDoubleBufferManager.ReleaseDoubleBuffer(specular);
}

void Material::RegisterForSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager)
{
	vector4FDoubleBufferManager.RegisterForSynchronization(ambient);
	vector4FDoubleBufferManager.RegisterForSynchronization(diffuse);
	vector4FDoubleBufferManager.RegisterForSynchronization(specular);
}

void Material::DeregisterFromSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager)
{
	vector4FDoubleBufferManager.DeregisterFromSynchronization(ambient);
	vector4FDoubleBufferManager.DeregisterFromSynchronization(diffuse);
	vector4FDoubleBufferManager.DeregisterFromSynchronization(specular);
}

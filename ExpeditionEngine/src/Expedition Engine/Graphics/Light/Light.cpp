#include "Light.h"

#include "../Graphics Resources/MaterialManager.h"

#include "../Graphics Resources/GraphicsResourcesManager.h"

const Light& Light::operator=(const Light& other)
{
	this->pMaterial->Ambient().SetUpdate(other.pMaterial->Ambient().GetUpdate());
	this->pMaterial->Diffuse().SetUpdate(other.pMaterial->Diffuse().GetUpdate());
	this->pMaterial->Specular().SetUpdate(other.pMaterial->Specular().GetUpdate());

	return *this;
}

void Light::SceneInitialize(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName)
{
	graphicsResourcesManager.AcquireMaterial(pMaterial);
	pMaterial->Initialize(Vector4F(0.0f, 0.0f, 0.0f, 1.0f));
	SceneInitializeChild(graphicsResourcesManager, sceneName);
}

void Light::SceneStart(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.RegisterForSynchronization(pMaterial);
	SceneStartChild(graphicsResourcesManager);
}

void Light::SceneStop(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.DeregisterFromSynchronization(pMaterial);
	SceneStopChild(graphicsResourcesManager);
}

void Light::SceneSanitize(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.ReleaseMaterial(pMaterial);
	SceneSanitizeChild(graphicsResourcesManager);
}

void Light::SetPhongADS(const Vector4F& amb, const Vector4F& diff, const Vector4F& spec)
{
	pMaterial->Ambient().SetUpdate(amb);
	pMaterial->Diffuse().SetUpdate(diff);
	pMaterial->Specular().SetUpdate(spec);
}
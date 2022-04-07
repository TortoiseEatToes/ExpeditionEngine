#include "PointLight.h"

#include "../Graphics Resources/GraphicsResourcesManager.h"

void PointLight::SetParameters(const Vector4F& pos, const Vector4F& att, const float& range, const Vector4F& amb, const Vector4F& diff, const Vector4F& spec)
{
	SetPhongADS(amb, diff, spec);

	position.GetCurrentObject().SetUpdate(pos);
	attenuation.GetCurrentObject().SetUpdate(Vector4F(att[x],att[y],att[z],range));
}

void PointLight::SceneInitializeChild(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName)
{
	graphicsResourcesManager.AcquireDoubleBuffer(position);
	graphicsResourcesManager.AcquireDoubleBuffer(attenuation);

	position.GetCurrentObject().Initialize(Vector4F(0.0f, 0.0f, 0.0f, 0.0f));
	attenuation.GetCurrentObject().Initialize(Vector4F(0.0f, 0.0f, 0.0f, 0.0f));
}

void PointLight::SceneStartChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.RegisterForSynchronization(position);
	graphicsResourcesManager.RegisterForSynchronization(attenuation);
}

void PointLight::SceneStopChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.DeregisterFromSynchronization(position);
	graphicsResourcesManager.DeregisterFromSynchronization(attenuation);
}

void PointLight::SceneSanitizeChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.ReleaseDoubleBuffer(position);
	graphicsResourcesManager.ReleaseDoubleBuffer(attenuation);
}
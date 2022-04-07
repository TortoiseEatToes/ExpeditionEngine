#include "DirectionalLight.h"

#include "../Graphics Resources/GraphicsResourcesManager.h"

void DirectionalLight::SetParameters(const Vector4F& dirc, const Vector4F& amb, const Vector4F& diff, const Vector4F& spec) 
{
	SetPhongADS(amb, diff, spec);

	direction.GetCurrentObject().SetUpdate(dirc);
}

void DirectionalLight::SetShadowParameters(const int& shadowMapSize, const Vector4F& sceneCenter, const float& sceneLength, const int& offset)
{
	shadow.SetShadowParameters(shadowMapSize, sceneCenter, sceneLength, direction.GetCurrentObject().GetUpdate(), offset);
}

void DirectionalLight::SceneInitializeChild(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName)
{
	graphicsResourcesManager.AcquireDoubleBuffer(direction);
	direction.GetCurrentObject().Initialize(Vector4F(0.5f, 0.5f, 0.5f));
	shadow.Initialize(sceneName);
}

void DirectionalLight::SceneStartChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.RegisterForSynchronization(direction);
}

void DirectionalLight::SceneStopChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.DeregisterFromSynchronization(direction);
}

void DirectionalLight::SceneSanitizeChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.ReleaseDoubleBuffer(direction);
	shadow.Sanitize();
}
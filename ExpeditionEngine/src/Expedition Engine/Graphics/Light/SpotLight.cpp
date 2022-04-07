#include "SpotLight.h"

#include "../Graphics Resources/GraphicsResourcesManager.h"

void SpotLight::SetParameters(const Vector4F& pos, const Vector4F& dirc, const Vector4F& att, const float& range, const float& exp, const Vector4F& amb, const Vector4F& diff, const Vector4F& spec)
{
	SetPhongADS(amb, diff, spec);

	position.GetCurrentObject().SetUpdate(pos);
	attenuation.GetCurrentObject().SetUpdate(Vector4F(att[x], att[y], att[z], range));
	direction.GetCurrentObject().SetUpdate(Vector4F(dirc[x], dirc[y], dirc[z], exp));
}

void SpotLight::SetShadowParameters(const int& shadowMapSize, const int& offset)
{
	static float cutoffValue = 0.00001f;

	float cutoff = acosf(powf(cutoffValue, 1.0f / GetDirection()->GetUpdate().W()));

	//cutoff *= (360 / (3.14159f * 2));

	shadow.SetShadowParameters(shadowMapSize, cutoff, GetAttenuation()->GetUpdate().W(), direction.GetCurrentObject().GetUpdate(), position.GetCurrentObject().GetUpdate(), offset);
}

void SpotLight::SceneInitializeChild(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName)
{
	graphicsResourcesManager.AcquireDoubleBuffer(position);
	graphicsResourcesManager.AcquireDoubleBuffer(attenuation);
	graphicsResourcesManager.AcquireDoubleBuffer(direction);

	position.GetCurrentObject().Initialize(Vector4F(0.0f, 0.0f, 0.0f, 0.0f));
	attenuation.GetCurrentObject().Initialize(Vector4F(0.0f, 0.0f, 0.0f, 0.0f));
	direction.GetCurrentObject().Initialize(Vector4F(0.0f, 0.0f, 0.0f, 0.0f));
	shadow.Initialize(sceneName);
}

void SpotLight::SceneStartChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.RegisterForSynchronization(position);
	graphicsResourcesManager.RegisterForSynchronization(attenuation);
	graphicsResourcesManager.RegisterForSynchronization(direction);
}

void SpotLight::SceneStopChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.DeregisterFromSynchronization(position);
	graphicsResourcesManager.DeregisterFromSynchronization(attenuation);
	graphicsResourcesManager.DeregisterFromSynchronization(direction);
}

void SpotLight::SceneSanitizeChild(GraphicsResourcesManager& graphicsResourcesManager)
{
	graphicsResourcesManager.ReleaseDoubleBuffer(position);
	graphicsResourcesManager.ReleaseDoubleBuffer(attenuation);
	graphicsResourcesManager.ReleaseDoubleBuffer(direction);

	shadow.Sanitize();
}
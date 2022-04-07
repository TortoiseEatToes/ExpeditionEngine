#include "LightManager.h"
#include <assert.h>
#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"
#include "../../DX12App/DXApp/DXApp_12.h"

#include <math.h>

LightManager::LightManager()
{
	//ClearAllLights();
}

void LightManager::UpdateDirectionLight(const int& index, const Vector4F& dirc, const Vector4F& amb, const Vector4F& diff, const Vector4F& spec) 
{
	assert((index < NumberOfDirectionalLightsPerScene));
	dircLightList[index].SetParameters(dirc, amb, diff, spec);
}

void LightManager::UpdateSpotLight(const int& index, const Vector4F& pos, const Vector4F& dirc, const Vector4F& att, const float& range, const float& exp,
	const Vector4F& amb, const Vector4F& diff, const Vector4F& spec)
{
	assert((index < NumberOfSpotLightsPerScene));
	spotLightList[index].SetParameters(pos, dirc, att, range, exp, amb, diff, spec);

	UpdateSpotLightShadows(index);
}

void LightManager::UpdatePointLight(const int& index, const Vector4F& pos, const Vector4F& att, const float& range, const Vector4F& amb,
	const Vector4F& diff, const Vector4F& spec)
{
	assert((index < NumberOfPointLightsPerScene));
	pointLightList[index].SetParameters(pos, att, range, amb, diff, spec);
}

void LightManager::ClearDirectionalLight(const int& index) {

	Vector4F clearVect = Vector4F(0, 0, 0, 1);

	dircLightList[index].SetParameters(clearVect, clearVect, clearVect, clearVect);
}

void LightManager::ClearSpotLight(const int& index) {

	Vector4F clearVect = Vector4F(0, 0, 0, 1);

	spotLightList[index].SetParameters(clearVect, clearVect, clearVect, 0, 0, clearVect, clearVect, clearVect);
}

void LightManager::ClearPointLight(const int& index) {

	Vector4F clearVect = Vector4F(0, 0, 0, 1);

	pointLightList[index].SetParameters(clearVect, clearVect, 0, clearVect, clearVect, clearVect);
}

void LightManager::ClearAllLights() {

	for (int i = 0; i < NumberOfDirectionalLightsPerScene; i++)
		ClearDirectionalLight(i);

	for (int i = 0; i < NumberOfPointLightsPerScene; i++)
		ClearPointLight(i);

	for (int i = 0; i < NumberOfSpotLightsPerScene; i++)
		ClearSpotLight(i);
}

void LightManager::InitializeDirectionalLightShadow(const int& lightIndex, const int& shadowMapSize, const Vector4F& sceneCenter, const int& sceneLength)
{
	dircLightList[lightIndex].SetShadowParameters(shadowMapSize, sceneCenter, static_cast<float>(sceneLength), lightIndex);
	DXApp_12::UpdateShadowDescriptorsDirectional(lightIndex);
}

void LightManager::InitializeSpotLightShadow(const int& lightIndex, const int& shadowMapSize)
{
	spotLightList[lightIndex].SetShadowParameters(shadowMapSize, lightIndex + NumberOfDirectionalLightsPerScene);
	DXApp_12::UpdateShadowDescriptorsSpotLight(lightIndex + NumberOfDirectionalLightsPerScene);
}

void LightManager::EnableDirectionLightShadows(int lightIndex, const SceneName& inScene)
{
	GraphicsSceneManagerAttorney::LightControl::RegisterShadow(inScene, dircLightList[lightIndex].GetShadow());
}

void LightManager::DisableDirectionLightShadows(int lightIndex, const SceneName& inScene)
{
	GraphicsSceneManagerAttorney::LightControl::DeregisterShadow(inScene, dircLightList[lightIndex].GetShadow());
}

void LightManager::EnableSpotLightShadows(int lightIndex, const SceneName& inScene)
{
	GraphicsSceneManagerAttorney::LightControl::RegisterShadow(inScene, spotLightList[lightIndex].GetShadow());

}

void LightManager::DisableSpotLightShadows(int lightIndex, const SceneName& inScene)
{
	GraphicsSceneManagerAttorney::LightControl::DeregisterShadow(inScene, spotLightList[lightIndex].GetShadow());
}

void LightManager::UpdateSpotLightShadows(int lightIndex)
{
	spotLightList[lightIndex].GetShadow()->UpdateCamera(spotLightList[lightIndex].GetDirection()->GetUpdate(), spotLightList[lightIndex].GetPosition()->GetUpdate(), 
		spotLightList[lightIndex].GetAttenuation()->GetUpdate().W(), spotLightList[lightIndex].GetDirection()->GetUpdate().W());
}

void LightManager::SceneInitialize(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName)
{
	for (int i = 0; i < NumberOfDirectionalLightsPerScene; i++)
		dircLightList[i].SceneInitialize(graphicsResourcesManager, sceneName);

	for (int i = 0; i < NumberOfSpotLightsPerScene; i++)
		spotLightList[i].SceneInitialize(graphicsResourcesManager, sceneName);

	for (int i = 0; i < NumberOfPointLightsPerScene; i++)
		pointLightList[i].SceneInitialize(graphicsResourcesManager, sceneName);
}

void LightManager::SceneStart(GraphicsResourcesManager& graphicsResourcesManager)
{
	for (int i = 0; i < NumberOfDirectionalLightsPerScene; i++)
		dircLightList[i].SceneStart(graphicsResourcesManager);

	for (int i = 0; i < NumberOfSpotLightsPerScene; i++)
		spotLightList[i].SceneStart(graphicsResourcesManager);

	for (int i = 0; i < NumberOfPointLightsPerScene; i++)
		pointLightList[i].SceneStart(graphicsResourcesManager);
}

void LightManager::SceneStop(GraphicsResourcesManager& graphicsResourcesManager)
{
	for (int i = 0; i < NumberOfDirectionalLightsPerScene; i++)
		dircLightList[i].SceneStop(graphicsResourcesManager);

	for (int i = 0; i < NumberOfSpotLightsPerScene; i++)
		spotLightList[i].SceneStop(graphicsResourcesManager);

	for (int i = 0; i < NumberOfPointLightsPerScene; i++)
		pointLightList[i].SceneStop(graphicsResourcesManager);
}

void LightManager::SceneSanitize(GraphicsResourcesManager& graphicsResourcesManager)
{
	for (int i = 0; i < NumberOfDirectionalLightsPerScene; i++)
		dircLightList[i].SceneSanitize(graphicsResourcesManager);

	for (int i = 0; i < NumberOfSpotLightsPerScene; i++)
		spotLightList[i].SceneSanitize(graphicsResourcesManager);

	for (int i = 0; i < NumberOfPointLightsPerScene; i++)
		pointLightList[i].SceneSanitize(graphicsResourcesManager);
}

LightManager::~LightManager()
{
}

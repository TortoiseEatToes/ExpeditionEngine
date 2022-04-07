#ifndef LightManager_h
#define LightManager_h

#include <list>
#include <assert.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "../../Math/Vector/Vector4F.h"

#include "../../../Expedition Resources/LightSettings.h"
#include "../../../Expedition Resources/SceneSettings.h"

#include "../../DX12App/Shadows/ShadowManager.h"

class LightBaseCmd;
class GraphicsResourcesManager;
class GraphicsScene;

/// \ingroup LIGHT
/// \{

class LightManager
{

	friend class LightManagerAttorney;

public:

	static const int MAX_DIRC_LIGHTS = 3;
	static const int MAX_POINT_LIGHTS = 10;
	static const int MAX_SPOT_LIGHTS = 10;

private:

	DirectionalLight dircLightList[NumberOfDirectionalLightsPerScene];
	SpotLight spotLightList[NumberOfSpotLightsPerScene];
	PointLight pointLightList[NumberOfPointLightsPerScene];

	ShadowManager shadowMgr;

public:

	LightManager();
	~LightManager();
	LightManager(LightManager&&) = delete;
	LightManager(const LightManager&) = delete;
	const LightManager& operator = (LightManager&&) = delete;
	const LightManager& operator = (const LightManager&) = delete;

	ShadowManager* GetShadowMgr() { return &shadowMgr; }

	/// \ingroup LIGHT
	/// \brief Returns the Directional Light associated with given number
	DirectionalLight& GetDirectionalLight(const int& i) { return dircLightList[i]; };

	/// \ingroup LIGHT
	/// \brief Returns the Spot Light associated with given number
	SpotLight& GetSpotLight(const int& i) 
	{  
		assert(i >= 0 && i < NumberOfSpotLightsPerScene);
		return spotLightList[i]; 
	}

	/// \ingroup LIGHT
	/// \brief Returns the Point Light associated with given number
	PointLight& GetPointLight(const int& i) { return pointLightList[i]; };


	/// \ingroup LIGHT
	/// \brief Updates Directional Light associated with given index.
	/// 
	/// \param index number of the light to be updated
	///	\param dirc Vector that repersents the direction the light should be in
	///	\param amb Vector that repersents the ambient light produced bt the light. Default setting is (.5, .5, .5, 1)
	///	\param diff Vector that repersents the diffuse light produced by the light. Default setting is (.5, .5, .5, 1)
	///	\param spec Vector that repersents the specular light produced by the light. Default setting is (.5, .5, .5, 1)
	void UpdateDirectionLight(const int& index, const Vector4F& dirc, const Vector4F& amb = Vector4F(.5f, .5f, .5f, 1), const Vector4F& diff = Vector4F(.5f, .5f, .5f, 1),
		const Vector4F& spec = Vector4F(.5f, .5f, .5f, 1));

	/// \ingroup LIGHT
	/// \brief Updates the SpotLight associated with given index.
	/// 
	/// \param index number of the light to be updated
	///	\param pos Vector that repersents the position of the light
	///	\param dirc Vector that repersents the direction the light should be in
	///	\param att Vector that repersents the attenuation of the light
	///	\param range Float that repersents the range that the light will affect
	///	\param exp Float that repersents the spot exponent of the light.
	///	\param amb Vector that repersents the ambient light produced bt the light. Default setting is (.5, .5, .5, 1)
	///	\param diff Vector that repersents the diffuse light produced by the light. Default setting is (.5, .5, .5, 1)
	///	\param spec Vector that repersents the specular light produced by the light. Default setting is (.5, .5, .5, 1)
	void UpdateSpotLight(const int& index, const Vector4F& pos, const Vector4F& dirc, const Vector4F& att, const float& range, const float& exp,
		const Vector4F& amb = Vector4F(.5f, .5f, .5f, 1), const Vector4F& diff = Vector4F(.5f, .5f, .5f, 1), const Vector4F& spec = Vector4F(.5f, .5f, .5f, 1));

	/// \ingroup LIGHT
	/// \brief Updates the PointLight associated with given index.
	/// 
	/// \param index number of the light to be updated
	///	\param pos Vector that repersents the position of the light
	///	\param att Vector that repersents the attenuation of the light
	///	\param range Float that repersents the range that the light will affect
	///	\param amb Vector that repersents the ambient light produced bt the light. Default setting is (.5, .5, .5, 1)
	///	\param diff Vector that repersents the diffuse light produced by the light. Default setting is (.5, .5, .5, 1)
	///	\param spec Vector that repersents the specular light produced by the light. Default setting is (.5, .5, .5, 1)
	void UpdatePointLight(const int& index, const Vector4F& pos, const Vector4F& att, const float& range, const Vector4F& amb = Vector4F(.5f, .5f, .5f, 1),
		const Vector4F& diff = Vector4F(.5f, .5f, .5f, 1), const Vector4F& spec = Vector4F(.5f, .5f, .5f, 1));

	/// \ingroup LIGHT
	/// \brief resets Directional Light at given index to its default values. essentially removes it from the scene
	void ClearDirectionalLight(const int& index);

	/// \ingroup LIGHT
	/// \brief resets SpotLight at given index to its default values. essentially removes it from the scene
	void ClearSpotLight(const int& index);

	/// \ingroup LIGHT
	/// \brief resets PointLight at given index to its default values. essentially removes it from the scene
	void ClearPointLight(const int& index);

	/// \ingroup LIGHT
	/// \brief resets All Lights in the scene
	void ClearAllLights();
	
	void InitializeDirectionalLightShadow(const int& lightIndex, const int& shadowMapSize, const Vector4F& sceneCenter, const int& sceneLength);
	void InitializeSpotLightShadow(const int& lightIndex, const int& shadowMapSize);

	void EnableDirectionLightShadows(int lightIndex, const SceneName& inScene);
	void DisableDirectionLightShadows(int lightIndex, const SceneName& inScene);

	void EnableSpotLightShadows(int lightIndex, const SceneName& inScene);
	void DisableSpotLightShadows(int lightIndex, const SceneName& inScene);
	void UpdateSpotLightShadows(int lightIndex);

	//Acquire all resources
	void SceneInitialize(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName);

	//Register all lights
	void SceneStart(GraphicsResourcesManager& graphicsResourcesManager);

	//Deregister all lights
	void SceneStop(GraphicsResourcesManager& graphicsResourcesManager);

	//Release all resources
	void SceneSanitize(GraphicsResourcesManager& graphicsResourcesManager);

};
/// \}
#endif LightManager_h
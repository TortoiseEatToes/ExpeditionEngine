#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Light.h"

#include "../../Containers/PooledResourceIterator.h"
#include "../Graphics Resources/Vector4FDoubleBuffer.h"

#include "../../DX12App/Shadows/Shadow.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight() = default;
	DirectionalLight(DirectionalLight&&) = delete;
	DirectionalLight(const DirectionalLight&) = delete;
	const DirectionalLight& operator = (DirectionalLight&&) = delete;
	const DirectionalLight& operator = (const DirectionalLight&) = delete;
	~DirectionalLight() = default;

	void SetParameters(const Vector4F& dirc, const Vector4F& amb = Vector4F(.5f, .5f, .5f, 1), const Vector4F& diff = Vector4F(.5f, .5f, .5f, 1), const Vector4F& spec = Vector4F(.5f, .5f, .5f, 1));
	void SetShadowParameters(const int& shadowMapSize, const Vector4F& sceneCenter, const float& sceneLength, const int& offset);
	Vector4FDoubleBuffer* GetDirection() { return &direction.GetCurrentObject(); }
   
	Shadow* GetShadow() { return &shadow; }

private:
	void SceneInitializeChild(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName) override;
	void SceneStartChild(GraphicsResourcesManager& graphicsResourcesManager) override;
	void SceneStopChild(GraphicsResourcesManager& graphicsResourcesManager) override;
	void SceneSanitizeChild(GraphicsResourcesManager& graphicsResourcesManager) override;


	PooledResourceIterator<Vector4FDoubleBuffer> direction;

	Shadow shadow;
};

#endif DirectionalLight_h
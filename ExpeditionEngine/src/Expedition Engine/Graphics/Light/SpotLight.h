#ifndef SpotLight_h
#define SpotLight_h

#include "Light.h"

#include "../../Containers/PooledResourceIterator.h"
#include "../Graphics Resources/Vector4FDoubleBuffer.h"

#include "../../DX12App/Shadows/Shadow.h"

class SpotLight : public Light
{
public:
	SpotLight() = default;
	SpotLight(SpotLight&&) = delete;
	SpotLight(const SpotLight&) = delete;
	const SpotLight& operator = (SpotLight&&) = delete;
	const SpotLight& operator = (const SpotLight&) = delete;
	~SpotLight() = default;

	void SetParameters(const Vector4F& pos, const Vector4F& dirc, const Vector4F& att, const float& range, const float& exp, const Vector4F& amb = Vector4F(.5f, .5f, .5f, 1), const Vector4F& diff = Vector4F(.5f, .5f, .5f, 1)
		, const Vector4F& spec = Vector4F(.5f, .5f, .5f, 1));

	void SetShadowParameters(const int& shadowMapSize, const int& offset);

	Vector4FDoubleBuffer* GetPosition() { return &position.GetCurrentObject(); }
	Vector4FDoubleBuffer* GetAttenuation() { return &attenuation.GetCurrentObject(); }
	Vector4FDoubleBuffer* GetDirection() { return &direction.GetCurrentObject(); }

	Shadow* GetShadow() { return &shadow; }

private:
	void SceneInitializeChild(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName) override;
	void SceneStartChild(GraphicsResourcesManager& graphicsResourcesManager) override;
	void SceneStopChild(GraphicsResourcesManager& graphicsResourcesManager) override;
	void SceneSanitizeChild(GraphicsResourcesManager& graphicsResourcesManager) override;

	PooledResourceIterator<Vector4FDoubleBuffer> position;
	PooledResourceIterator<Vector4FDoubleBuffer> attenuation;
	PooledResourceIterator<Vector4FDoubleBuffer> direction;

	Shadow shadow;
};

#endif SpotLight_h
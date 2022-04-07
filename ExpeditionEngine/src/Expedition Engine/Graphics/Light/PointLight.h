#ifndef PointLight_h
#define PointLight_h

#include "Light.h"

#include "../../Containers/PooledResourceIterator.h"
#include "../Graphics Resources/Vector4FDoubleBuffer.h"

class PointLight : public Light
{
public:
	PointLight() = default;
	PointLight(PointLight&&) = delete;
	PointLight(const PointLight&) = delete;
	const PointLight& operator = (PointLight&&) = delete;
	const PointLight& operator = (const PointLight&) = delete;
	~PointLight() = default;

	void SetParameters(const Vector4F& pos, const Vector4F& att, const float& range, const Vector4F& amb = Vector4F(.5f, .5f, .5f, 1), const Vector4F& diff = Vector4F(.5f, .5f, .5f, 1)
		, const Vector4F& spec = Vector4F(.5f, .5f, .5f, 1));

	Vector4FDoubleBuffer* GetPosition() { return &position.GetCurrentObject(); }
	Vector4FDoubleBuffer* GetAttenuation() { return &attenuation.GetCurrentObject(); }


private:
	void SceneInitializeChild(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName) override;
	void SceneStartChild(GraphicsResourcesManager& graphicsResourcesManager) override;
	void SceneStopChild(GraphicsResourcesManager& graphicsResourcesManager) override;
	void SceneSanitizeChild(GraphicsResourcesManager& graphicsResourcesManager) override;

	PooledResourceIterator<Vector4FDoubleBuffer> position;
	PooledResourceIterator<Vector4FDoubleBuffer> attenuation;
};

#endif PointLight_h
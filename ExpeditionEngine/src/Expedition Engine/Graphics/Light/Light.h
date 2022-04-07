#ifndef Light_h
#define Light_h

#include "../../Math/Vector/Vector4F.h"

class Material;
class GraphicsResourcesManager;
enum SceneName;

class Light : public Align16
{
public:
	Light() = default;
	//Light(const Vector4F& amb, const Vector4F& diff, const Vector4F& spec);
	Light(Light&&) = delete;
	Light(const Light&) = delete;
	const Light& operator = (Light&&) = delete;
	const Light& operator = (const Light&);
	~Light()= default;

	Material* GetMaterial() { return pMaterial; }

	void SceneInitialize(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName);
	void SceneStart(GraphicsResourcesManager& graphicsResourcesManager);
	void SceneStop(GraphicsResourcesManager& graphicsResourcesManager);
	void SceneSanitize(GraphicsResourcesManager& graphicsResourcesManager);
	

protected:
	void SetPhongADS(const Vector4F& amb, const Vector4F& diff, const Vector4F& spec);

	virtual void SceneInitializeChild(GraphicsResourcesManager& graphicsResourcesManager, const SceneName& sceneName) {};
	virtual void SceneStartChild(GraphicsResourcesManager& graphicsResourcesManager) {};
	virtual void SceneStopChild(GraphicsResourcesManager& graphicsResourcesManager) {};
	virtual void SceneSanitizeChild(GraphicsResourcesManager& graphicsResourcesManager) {};

private:

	Material* pMaterial;
};

#endif Light_h
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../Containers/Queue.h"
#include "../Containers/List.h"
#include "../../Expedition Resources/ShaderSettings.h"
#include "../Graphics/Light/LightManager.h"
#include "../Graphics/GraphicsObjects/Manager/GO_Data_Manager.h"
#include "../Graphics/Graphics Resources/GraphicsResourcesManager.h"
#include "../Graphics/Particles/ParticleManagerAttorney.h"

class GraphicsSceneCommand;
class GraphicsObject;
class ParticleEmitter;
class Camera;
class Scene;
enum SceneName;

class GraphicsScene
{
	friend class GraphicsSceneAttorney;
public:
	GraphicsScene();
	GraphicsScene(GraphicsScene&& other) = delete;
	GraphicsScene(const GraphicsScene& other) = delete;
	GraphicsScene& operator= (GraphicsScene&& other) = delete;
	GraphicsScene& operator= (const GraphicsScene& other) = delete;
	~GraphicsScene();

	LightManager* GetLightMgr() { return &LightMgr; }

	void SceneInitialize(const SceneName& sceneName);
	void SceneStart();
	void SceneStop();
	void SceneSanitize();

	void Synchronize();

	void ProcessCommands();

	GraphicsResourcesManager& GetGraphicsResourcesManager()
	{
		return graphicsResourcesManager;
	}

	ParticleManager& GetParticleManager()
	{
		return particleManager;
	}



private:
	GO_Data_Manager& GetGraphicsObjectDataManager()
	{
		return graphicsObjectDataManager;
	}

	void Render();
	void RenderParticles();

	void InsertCommand(GraphicsSceneCommand* pCommand);

	void RegisterGraphicsObjectColor(GraphicsObject* pGO);
	void DeregisterGraphicsObjectColor(GraphicsObject* pGO);

	void RegisterGraphicsObjectColorLight(GraphicsObject* pGO);
	void DeregisterGraphicsObjectColorLight(GraphicsObject* pGO);

	void RegisterGraphicsObjectTexture(GraphicsObject* pGO);
	void DeregisterGraphicsObjectTexture(GraphicsObject* pGO);

	void RegisterGraphicsObjectTextureLight(GraphicsObject* pGO);
	void DeregisterGraphicsObjectTextureLight(GraphicsObject* pGO);

	GO_Data_Manager graphicsObjectDataManager;
	GraphicsResourcesManager graphicsResourcesManager;
	ParticleManager particleManager;

	Queue<GraphicsSceneCommand*> commandQueue;
	GraphicsSceneCommand* pTempCommand;

	LightManager LightMgr;
};
#endif // !GRAPHICSSCENE_H
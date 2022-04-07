#pragma once

#include "GraphicsScene.h"
#include "../../Expedition Resources/SceneSettings.h"

#include "Commands/Registration Actions/Base/ActionDeregisterBase.h"
#include "Commands/Registration Actions/Base/ActionRegisterBase.h"
#include "Commands/Registration Actions/ActionRegisterColor.h"
#include "Commands/Registration Actions/ActionDeregisterColor.h"
#include "Commands/Registration Actions/ActionRegisterColorLight.h"
#include "Commands/Registration Actions/ActionDeregisterColorLight.h"
#include "Commands/Registration Actions/ActionRegisterTexture.h"
#include "Commands/Registration Actions/ActionDeregisterTexture.h"
#include "Commands/Registration Actions/ActionRegisterTextureLight.h"
#include "Commands/Registration Actions/ActionDeregisterTextureLight.h"
#include "../DX12App/Shadows/ActionRegisterShadow.h"
#include "../DX12App/Shadows/ActionDeregisterShadow.h"

#include "Commands/GraphicsObjectRegistrationCommand.h"
#include "../DX12App/Shadows/ShadowCmd.h"

#include "../Containers/Pool.h"

class GraphicsObject;
class CMD_ParticleBurst;
struct ParticleBurstData;

class GraphicsSceneManager : public Align16
{
public:

	static GraphicsScene* GetCurrentScene() { return Instance().currentScene; }
	static GraphicsScene* GetScene(SceneName name) { return &Instance().graphicsScenesArray[name]; }

private:
	friend class GraphicsSceneManagerAttorney;

	static void RenderFrame()
	{
		Instance().privRenderFrame();
	}
	void privRenderFrame();

	static void RenderParticles()
	{
		Instance().privRenderParticles();
	}
	void privRenderParticles();

	static void Initialize()
	{
		pInstance = new GraphicsSceneManager();
	}

	static GraphicsSceneManager& Instance()
	{
		return *pInstance;
	}

	static void Terminate()
	{
		delete pInstance;
	}

	GraphicsSceneManager();
	GraphicsSceneManager(const GraphicsSceneManager& other) = delete;
	GraphicsSceneManager& operator= (const GraphicsSceneManager& other) = delete;
	~GraphicsSceneManager();


	static GraphicsSceneManager* pInstance;

	static void SetActiveCamera(Camera* pCamera)
	{
		Instance().privSetActiveCamera(pCamera);
	}
	void privSetActiveCamera(Camera* pCamera);


	GraphicsScene graphicsScenesArray[NumberOfScenes];
	GraphicsScene* currentScene;

	//------------------  Scene Manager Controls -----------------
	static void SetStartingScene(const SceneName& name)
	{
		Instance().privSetStartingScene(name);
	}
	void privSetStartingScene(const SceneName& name);

	static void SetCurrentScene(const SceneName& name)
	{
		Instance().privSetCurrentScene(name);
	}
	void privSetCurrentScene(const SceneName& name);

	static void InitializeScene(const SceneName& name)
	{
		Instance().privInitializeScene(name);
	}
	void privInitializeScene(const SceneName& name);

	static void SantitizeScene(const SceneName& name)
	{
		Instance().privSantitizeScene(name);
	}
	void privSantitizeScene(const SceneName& name);
	//-------------------------------------------------------------

	static void RecycleCommand(const GraphicsObjectRegistrationCommand* pCmd) 
	{
		//Instance().commandPool.RecycleObject(pCmd);
	}

	static void RecycleCommand(const CMD_ParticleBurst* pParticleCommand) 
	{
		//Instance().particleCommandPool.RecycleObject(pParticleCommand);
	}

	static void ProcessCurrentSceneCommands()
	{
		Instance().privProcessCurrentSceneCommands();
	}
	void privProcessCurrentSceneCommands();

	static void Synchronize()
	{
		Instance().privSynchronize();
	}
	void privSynchronize();

	static void RegisterGraphicsObjectColor(const SceneName& sceneName, GraphicsObject* pGO) 
	{
		Instance().privRegisterGraphicsObjectColor(sceneName, pGO);
	}
	void privRegisterGraphicsObjectColor(const SceneName& sceneName, GraphicsObject* pGO);

	static void DeregisterGraphicsObjectColor(const SceneName& sceneName, GraphicsObject* pGO)
	{
		Instance().privDeregisterGraphicsObjectColor(sceneName, pGO);
	}
	void privDeregisterGraphicsObjectColor(const SceneName& sceneName, GraphicsObject* pGO);

	static void RegisterGraphicsObjectColorLight(const SceneName& sceneName, GraphicsObject* pGO)
	{
		Instance().privRegisterGraphicsObjectColorLight(sceneName, pGO);
	}
	void privRegisterGraphicsObjectColorLight(const SceneName& sceneName, GraphicsObject* pGO);

	static void DeregisterGraphicsObjectColorLight(const SceneName& sceneName, GraphicsObject* pGO)
	{
		Instance().privDeregisterGraphicsObjectColorLight(sceneName, pGO);
	}
	void privDeregisterGraphicsObjectColorLight(const SceneName& sceneName, GraphicsObject* pGO);

	static void RegisterGraphicsObjectTexture(const SceneName& sceneName, GraphicsObject* pGO)
	{
		Instance().privRegisterGraphicsObjectTexture(sceneName, pGO);
	}
	void privRegisterGraphicsObjectTexture(const SceneName& sceneName, GraphicsObject* pGO);

	static void DeregisterGraphicsObjectTexture(const SceneName& sceneName, GraphicsObject* pGO)
	{
		Instance().privDeregisterGraphicsObjectTexture(sceneName, pGO);
	}
	void privDeregisterGraphicsObjectTexture(const SceneName& sceneName, GraphicsObject* pGO);

	static void RegisterGraphicsObjectTextureLight(const SceneName& sceneName, GraphicsObject* pGO)
	{
		Instance().privRegisterGraphicsObjectTextureLight(sceneName, pGO);
	}
	void privRegisterGraphicsObjectTextureLight(const SceneName& sceneName, GraphicsObject* pGO);

	static void DeregisterGraphicsObjectTextureLight(const SceneName& sceneName, GraphicsObject* pGO)
	{
		Instance().privDeregisterGraphicsObjectTextureLight(sceneName, pGO);
	}
	void privDeregisterGraphicsObjectTextureLight(const SceneName& sceneName, GraphicsObject* pGO);

	static void RequestParticleBurst(const SceneName& sceneName, const ParticleBurstData& particleBurstData)
	{
		Instance().privRequestParticleBurst(sceneName, particleBurstData);
	}
	void privRequestParticleBurst(const SceneName& sceneName, const ParticleBurstData& particleBurstData);

	static void AllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, const int maxNumberOfParticles)
	{
		Instance().privAllocateParticleMemory(particleName, pModel, pTexture, maxNumberOfParticles);
	}
	void privAllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, const int maxNumberOfParticles);

	static void RegisterShadow(const SceneName& sceneName, Shadow* inShadow)
	{
		Instance().privRegisterShadow(sceneName, inShadow);
	}
	void privRegisterShadow(const SceneName& sceneName, Shadow* inShadow);

	static void DeregisterShadow(const SceneName& sceneName, Shadow* inShadow)
	{
		Instance().privDeregisterShadow(sceneName, inShadow);
	}
	void privDeregisterShadow(const SceneName& sceneName, Shadow* inShadow);

	static GraphicsResourcesManager& GetGraphicsResourcesManager(const SceneName& sceneName)
	{
		return Instance().privGetGraphicsResourcesManager(sceneName);
	}
	GraphicsResourcesManager& privGetGraphicsResourcesManager(const SceneName& sceneName);

	//Scene Registration command
	Pool<GraphicsObjectRegistrationCommand> commandPool;
	GraphicsObjectRegistrationCommand* pTempCommand;

	//Shadow Commands
	Pool<ShadowCmd> shadowCmdPool;
	ShadowCmd* pTempShadowCmd;

	Pool<CMD_ParticleBurst> particleCommandPool;
	CMD_ParticleBurst* pTempParticleCommand;


	//--------------------------- Actions -----------------------------------
	ActionRegisterColor actionRegColor;
	ActionDeregisterColor actionDeregColor;

	ActionRegisterColorLight actionRegColorLight;
	ActionDeregisterColorLight actionDeregColorLight;

	ActionRegisterTexture actionRegTexture;
	ActionDeregisterTexture actionDeregTexture;

	ActionRegisterTextureLight actionRegTextureLight;
	ActionDeregisterTextureLight actionDeregTextureLight;

	ActionRegisterShadow actionRegShadow;
	ActionDeregisterShadow actionDeregShadow;
	//---------------------------------------------------------------------------------------
};
#include "GraphicsSceneManager.h"
#include "../Engine/ExpeditionEngineAttorney.h"
#include "GraphicsSceneAttorney.h"

#include "Commands/CMD_ParticleBurst.h"

GraphicsSceneManager* GraphicsSceneManager::pInstance = nullptr;

GraphicsSceneManager::GraphicsSceneManager()
{
	currentScene = &graphicsScenesArray[startingScene];
}

void GraphicsSceneManager::privRenderFrame()
{
	GraphicsSceneAttorney::ManagerControls::Render(currentScene);
}

void GraphicsSceneManager::privRenderParticles()
{
	GraphicsSceneAttorney::ManagerControls::RenderParticles(currentScene);
}


void GraphicsSceneManager::privSetStartingScene(const SceneName& name)
{
	currentScene = &graphicsScenesArray[name];
	currentScene->SceneStart();
}

void GraphicsSceneManager::privSetCurrentScene(const SceneName& name)
{
	currentScene->SceneStop();
	currentScene = &graphicsScenesArray[name];
	currentScene->SceneStart();
}

void GraphicsSceneManager::privInitializeScene(const SceneName& name)
{
	graphicsScenesArray[name].SceneInitialize(name);
}

void GraphicsSceneManager::privSantitizeScene(const SceneName& name)
{
	if (currentScene == &graphicsScenesArray[name])
	{
		currentScene->SceneStop();
	}
	graphicsScenesArray[name].SceneSanitize();
}

void GraphicsSceneManager::privProcessCurrentSceneCommands()
{
	currentScene->ProcessCommands();
}

void GraphicsSceneManager::privSynchronize()
{
	currentScene->Synchronize();
}

void GraphicsSceneManager::privRegisterGraphicsObjectColor(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegColor, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privDeregisterGraphicsObjectColor(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregColor, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privRegisterGraphicsObjectColorLight(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegColorLight, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privDeregisterGraphicsObjectColorLight(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregColorLight, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privRegisterGraphicsObjectTexture(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegTexture, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privDeregisterGraphicsObjectTexture(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregTexture, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privRegisterGraphicsObjectTextureLight(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegTextureLight, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privDeregisterGraphicsObjectTextureLight(const SceneName& sceneName, GraphicsObject* pGO)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregTextureLight, pGO);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempCommand);
}

void GraphicsSceneManager::privRequestParticleBurst(const SceneName& sceneName, const ParticleBurstData& particleBurstData)
{
	pTempParticleCommand = particleCommandPool.GetPooledObject();
	pTempParticleCommand->SetData(particleBurstData);
	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempParticleCommand);
}

void GraphicsSceneManager::privAllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, const int maxNumberOfParticles)
{
	for (int i = 0; i< NumberOfScenes; ++i)
	{
		graphicsScenesArray[i].GetParticleManager().AllocateParticleMemory(particleName, pModel, pTexture, maxNumberOfParticles);
	}
}

void GraphicsSceneManager::privRegisterShadow(const SceneName& sceneName, Shadow* inShadow)
{
	pTempShadowCmd = shadowCmdPool.GetPooledObject();
	pTempShadowCmd->Initialize(actionRegShadow, inShadow);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempShadowCmd);
}

void GraphicsSceneManager::privDeregisterShadow(const SceneName& sceneName, Shadow* inShadow)
{
	pTempShadowCmd = shadowCmdPool.GetPooledObject();
	pTempShadowCmd->Initialize(actionDeregShadow, inShadow);

	GraphicsSceneAttorney::ManagerControls::InsertCommand(&graphicsScenesArray[sceneName], pTempShadowCmd);
}

GraphicsResourcesManager& GraphicsSceneManager::privGetGraphicsResourcesManager(const SceneName& sceneName)
{
	return graphicsScenesArray[sceneName].GetGraphicsResourcesManager();
}

void GraphicsSceneManager::privSetActiveCamera(Camera* pCamera)
{
}


GraphicsSceneManager::~GraphicsSceneManager()
{

}

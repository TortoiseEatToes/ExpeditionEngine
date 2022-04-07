#pragma once
#include "GraphicsSceneManager.h"

class GraphicsSceneManagerAttorney
{
public:

	struct CommandCalls
	{
	private:
		friend class GraphicsObjectRegistrationCommand;
		static void RecycleCommand(GraphicsObjectRegistrationCommand* cmd) { GraphicsSceneManager::RecycleCommand(cmd); }
	};

	struct Command_ParticleBurstControl
	{
	private:
		friend class CMD_ParticleBurst;
		static void RecycleCommand(CMD_ParticleBurst* pCommand)
		{
			GraphicsSceneManager::RecycleCommand(pCommand);
		}
	};

	struct EngineControl
	{
	private:
		friend class ExpeditionEngine;
		static void Initialize()
		{
			GraphicsSceneManager::Initialize();
		}
		static void Terminate()
		{
			GraphicsSceneManager::Terminate();
		}
	};

	class RenderControl
	{
		friend class Task_RenderGraphicsObjects;

		static void RenderFrame()
		{
			GraphicsSceneManager::RenderFrame();
		}
	};

	class RenderParticlesControl
	{
		friend class Task_RenderParticles;

		static void RenderParticles()
		{
			GraphicsSceneManager::RenderParticles();
		}

	};

	class ResolveFrameControl
	{
		friend class Task_PostFrameStart;

		static void ProcessCurrentSceneCommands()
		{
			GraphicsSceneManager::ProcessCurrentSceneCommands();
		}
	};

	class SynchronizeControl
	{
	private:
		friend class Task_SynchronizeCurrentGraphicsScene;

		static void Synchronize()
		{
			GraphicsSceneManager::Synchronize();
		}
	};

	struct GraphicsObjectControl
	{
	private:
		friend class GraphicsObject;
		static void StartDrawingColor(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::RegisterGraphicsObjectColor(sceneName, pGO);
		}

		static void StartDrawingColorLight(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::RegisterGraphicsObjectColorLight(sceneName, pGO);
		}		

		static void StartDrawingTexture(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::RegisterGraphicsObjectTexture(sceneName, pGO);
		}		

		static void StartDrawingTextureLight(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::RegisterGraphicsObjectTextureLight(sceneName, pGO);
		}

		static void StopDrawingColor(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::DeregisterGraphicsObjectColor(sceneName, pGO);
		}

		static void StopDrawingColorLight(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::DeregisterGraphicsObjectColorLight(sceneName, pGO);
		}

		static void StopDrawingTexture(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::DeregisterGraphicsObjectTexture(sceneName, pGO);
		}

		static void StopDrawingTextureLight(const SceneName& sceneName, GraphicsObject* pGO)
		{
			GraphicsSceneManager::DeregisterGraphicsObjectTextureLight(sceneName, pGO);
		}
	};

	struct ParticleEmitterControl
	{
	private:
		friend class ParticleEmitter;

		static void RequestParticleBurst(const SceneName& sceneName, const ParticleBurstData& particleBurstData)
		{
			GraphicsSceneManager::RequestParticleBurst(sceneName, particleBurstData);
		}
	};

	struct SceneManagerControl
	{
	private:
		friend class SceneManager;

		static void SetStartingScene(const SceneName& name)
		{
			GraphicsSceneManager::SetStartingScene(name);
		}

		static void SetCurrentScene(const SceneName& name)
		{
			GraphicsSceneManager::SetCurrentScene(name);
		}

		static void InitializeScene(const SceneName& name)
		{
			GraphicsSceneManager::InitializeScene(name);
		}

		static void SantitizeScene(const SceneName& name)
		{
			GraphicsSceneManager::SantitizeScene(name);
		}
	};

	struct LightControl
	{
	private:
		friend class LightManager;
		static void RegisterShadow(const SceneName& sceneName, Shadow* inShadow) 
		{
			GraphicsSceneManager::RegisterShadow(sceneName, inShadow);
		}

		static void DeregisterShadow(const SceneName& sceneName, Shadow* inShadow)
		{
			GraphicsSceneManager::DeregisterShadow(sceneName, inShadow);
		}
	};

	struct ParticleSettingsManagerControl
	{
	private:
		friend class ParticleSettingsManager;
		static void AllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, int maxNumberOfParticles)
		{
			GraphicsSceneManager::AllocateParticleMemory(particleName, pModel, pTexture, maxNumberOfParticles);
		}
	};
};
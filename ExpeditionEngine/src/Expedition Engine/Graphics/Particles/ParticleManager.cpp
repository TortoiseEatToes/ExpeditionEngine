#include "ParticleManager.h"

#include "../../../Expedition Resources/GraphicsResourcesSettings.h"
#include "../../Engine/EngineUtilities.h"

#include "Particle.h"
#include "ParticleBurst.h"
#include "CMD_ParticleBurstInternal.h"

#include "../../DX12App/DXApp/DXApp_12.h"

#include "../../../Expedition Resources/EngineSettings.h"

#include "../../DX12App/Shaders/ShaderManager_12.h"
#include "../../DX12App/Shaders/ShaderBase_12.h"

#include "../GraphicsObjects/GO_Data_GPUObjects.h"

#include "../../Scenes/SceneManager.h"

#include "../../Math/MathTools.h"

ParticleManager::ParticleManager()
	:particleBurstPool(NumberOfParticleBursts), 
	commandPool(NumberOfParticleBursts),
	alarmQueue(NumberOfParticleBursts)
{

}

ParticleManager::~ParticleManager()
{
	//Remove all current requests
	while (commandQueue.GetSize() > 0)
	{
		commandQueue.Pop(currentCommandIterator);
		commandPool.ReleaseResource(currentCommandIterator);
	}

	//Kill all live bursts
	while (alarmQueue.Size() > 0)
	{
		PopBurstFromAlarm();
	}

	//Finally empty all of the memory
	for (int i = 0; i < NumberOfParticleTypes; ++i)
	{
		particleTypes[i].ReleaseAllResources(currentBurstIterator, currentParticleIterator, particlePool);
	}
}


void ParticleManager::ComputeAndRenderDX12(const Vector4F& cameraPosition)
{
	RemoveDeadParticleBursts(SceneManager::GetCurrentScene()->GetTimeManager().GetCurrentSceneTime()); //Burst iterator
	ProcessParticleBurstRequest(SceneManager::GetCurrentScene()->GetTimeManager().GetCurrentSceneTime()); //All 3 iterators

	DXApp_12::SetParticleRootSig();
	ShaderManager_12::Get(ShaderName::ParticleShader)->PrepareToRender(DXApp_12::GetParticleCommandList());


	//For particle type
	for (int i = 0; i < NumberOfParticleTypes; i++)
	{
		particleTypes[i].ComputeAndRenderDX12(currentBurstIterator, currentParticleIterator, SceneManager::GetCurrentScene()->GetTimeManager().GetDeltaTime(), cameraPosition);
	}
}

void ParticleManager::PushParticleBurstRequest(const ParticleBurstData& particleBurstData)
{
	if (commandPool.GetNumberOfAvailableResources() > 0)
	{
		commandPool.AcquireResource(currentCommandIterator);
		currentCommandIterator.GetCurrentObject().SetData(particleBurstData);
		commandQueue.Push(currentCommandIterator);
	}
	else
	{
		EngineUtilities::LogWarning("\nNOT ENOUGH PARTICLE BURST REQUEST OBJECTS");
	}
}

void ParticleManager::AllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, const int maxNumberOfParticles)
{
	particleTypes[static_cast<int>(particleName)].Instantiate(pModel, pTexture, maxNumberOfParticles);
}

//Uses burst iterator
void ParticleManager::RemoveDeadParticleBursts(const float& currentTime)
{
	while (alarmQueue.Size() > 0 && currentTime >= alarmQueue.PeekFrontPriority())
	{
		PopBurstFromAlarm();
	}
}

//Uses command iterator, burst iterator and particle iterator
void ParticleManager::ProcessParticleBurstRequest(const float& currentTime)
{
	while (commandQueue.GetSize() > 0)
	{
		commandQueue.Pop(currentCommandIterator);
		if (particleBurstPool.GetNumberOfAvailableResources() > 0)
		{
			particleBurstPool.AcquireResource(currentBurstIterator);
			currentBurstIterator.GetCurrentObject().Initialize(currentCommandIterator.GetCurrentObject().GetData());
			SpawnParticles(currentBurstIterator, currentCommandIterator.GetCurrentObject().GetData());
			particleTypes[currentCommandIterator.GetCurrentObject().GetData().particleName].PushBack(currentBurstIterator);
			alarmQueue.Push(currentTime + MathTools::RandomFloat(currentCommandIterator.GetCurrentObject().GetData().particleLifeMin, currentCommandIterator.GetCurrentObject().GetData().particleLifeMax)
				, currentBurstIterator.GetResource());
		}
		else
		{
			EngineUtilities::LogWarning("\nNOT ENOUGH PARTICLE BURST OBJECTS");
		}
		commandPool.ReleaseResource(currentCommandIterator);
	}
}

void ParticleManager::PopBurstFromAlarm()
{
	//Pop the dead burst off of the queue
	alarmQueue.Pop(pParticleBurstResource);
	currentBurstIterator.SetResource(pParticleBurstResource);

	//Remove the burst and all of it's data from all of the active lists
	particleTypes[currentBurstIterator.GetCurrentObject().GetParticleName()].Remove(currentBurstIterator);
	currentBurstIterator.GetCurrentObject().ReleaseAllParticles(currentParticleIterator, particlePool);
	particleBurstPool.ReleaseResource(currentBurstIterator);
}

//Uses burst iterator and particle iterator
void ParticleManager::SpawnParticles(PooledResourceIterator<ParticleBurst>& burstIterator, const ParticleBurstData& particleBurstData)
{
	bool hasEnoughParticles = true;
	int i = 0;
	while (hasEnoughParticles && i < particleBurstData.numberOfParticles)
	{
		if (particlePool.GetNumberOfAvailableResources() > 0)
		{
			particlePool.AcquireResource(currentParticleIterator);
			currentParticleIterator.GetCurrentParticle().Initialize(particleBurstData);
			currentBurstIterator.GetCurrentObject().AssignParticle(currentParticleIterator);
		}
		else
		{
			EngineUtilities::LogWarning("\nNOT ENOUGH PARTICLES!!!  Was short by: " + std::to_string(particleBurstData.numberOfParticles - i));
			hasEnoughParticles = false;
		}
		++i;
	}
}
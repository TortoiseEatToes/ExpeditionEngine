#pragma once

#include "../../Containers/ResourcePool.h"
#include "../../Containers/Queue_PooledResource.h"
#include "../../Containers/PriorityQueueArray.h"

#include "Particle_PooledResourcePool.h"
#include "../../../Expedition Resources/TextureSettings.h"

#include "ParticleType.h"

class ParticleBurst;
class Model;
class CMD_ParticleBurstInternal;

struct ParticleBurstData;

//Owns all of the particles in a graphics scene. Is used to create and render all particles.
class ParticleManager
{
public:
	ParticleManager();
	ParticleManager(const ParticleManager&) = delete;
	ParticleManager(ParticleManager&&) = delete;
	ParticleManager& operator=(const ParticleManager&) = delete;
	ParticleManager& operator=(ParticleManager&&) = delete;
	~ParticleManager();

	void PushParticleBurstRequest(const ParticleBurstData& particleBurstData);
	void AllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, const int maxNumberOfParticles);

	ParticleType& GetParticleType(const ParticleName& name)
	{
		return particleTypes[static_cast<int>(name)];
	}

private:

	friend class ParticleManagerAttorney;

	//Attorney Functions
	void ComputeAndRenderDX12(const Vector4F& cameraPosition);

	void RemoveDeadParticleBursts(const float& currentTime);
	void ProcessParticleBurstRequest(const float& currentTime);
	void PopBurstFromAlarm();
	void SpawnParticles(PooledResourceIterator<ParticleBurst>& burstIterator, const ParticleBurstData& particleBurstData);

	//Store all of our resources
	ResourcePool<ParticleBurst> particleBurstPool;
	Particle_PooledResourcePool particlePool;
	ResourcePool<CMD_ParticleBurstInternal> commandPool;

	//Containers for iterating over all of our resources
	PriorityQueueArray<PooledResource<ParticleBurst>*, float> alarmQueue;
	ParticleType particleTypes[NumberOfParticleTypes];
	Queue_PooledResource<CMD_ParticleBurstInternal> commandQueue;
	
	//Iterators for all of our containers
	PooledResourceIterator<CMD_ParticleBurstInternal> currentCommandIterator;
	PooledResourceIterator<ParticleBurst> currentBurstIterator;
	Particle_PooledResourceIterator currentParticleIterator;
	PooledResource<ParticleBurst>* pParticleBurstResource;
};
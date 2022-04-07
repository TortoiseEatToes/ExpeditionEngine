#pragma once

#include "../../Containers/List_PooledResource.h"
#include "../../Containers/PriorityQueueArray.h"
#include "../../../Expedition Resources/TextureSettings.h"

class Vector4F;
class Model;
class Texture;
class Particle;
class ParticleBurst;
class Particle_PooledResourceIterator;
class Particle_PooledResourcePool;

struct ID3D12Resource;

//User defined type of particles that is used for storing model data, texture data, and hardware instanced GPU data
class ParticleType
{
public:
	ParticleType();
	ParticleType(const ParticleType&) = delete;
	ParticleType(ParticleType&&) = delete;
	ParticleType& operator=(const ParticleType&) = delete;
	ParticleType& operator=(ParticleType&&) = delete;
	~ParticleType();

	void Instantiate(Model* pInitModel, Texture* pInitTexture, int initNumberOfParticles);

	void PushBack(PooledResourceIterator<ParticleBurst>& currentBurstIterator);
	void Remove(PooledResourceIterator<ParticleBurst>& currentBurstIterator);

	void ComputeAndRenderDX12(PooledResourceIterator<ParticleBurst>& currentBurstIterator, Particle_PooledResourceIterator& currentParticleIterator, const float& timeStep, const Vector4F& cameraPosition);

	void ReleaseAllResources(PooledResourceIterator<ParticleBurst>& currentBurstIterator, Particle_PooledResourceIterator& currentParticleIterator, Particle_PooledResourcePool& particlePool);

	TextureName& GetTextureName();

private:
	List_PooledResource<ParticleBurst> activeParticleBursts;


	Model* pModel = nullptr;
	Texture* pTexture = nullptr;

	ID3D12Resource* g_UploadBuffer = nullptr;
	void* mappedResource_12;

	PriorityQueueArray<Particle*, float> priorityQueue;
	//QueueArrayPriorityFloat<Particle*> priorityQueue;

	int numberOfInstances = -1;
	int numberOfParticles = 0;
};
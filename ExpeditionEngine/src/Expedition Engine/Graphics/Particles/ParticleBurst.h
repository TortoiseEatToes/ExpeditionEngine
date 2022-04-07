#pragma once

#include "../../../Expedition Resources/GraphicsResourcesSettings.h"

#include "Particle_PooledResourceList.h"
#include "../../Containers/PriorityQueueArray.h"

class Particle_PooledResourcePool;

//Contains a burst of particles
class ParticleBurst
{
public:
	ParticleBurst() = default;
	ParticleBurst(const ParticleBurst&) = delete;
	ParticleBurst(ParticleBurst&&) = delete;
	ParticleBurst& operator=(const ParticleBurst&) = delete;
	ParticleBurst& operator=(ParticleBurst&&) = delete;
	~ParticleBurst() = default;

	void Initialize(const ParticleBurstData& burstData);
	void AssignParticle(Particle_PooledResourceIterator& currentIterator);

	void ComputeAndRenderDX12(Particle_PooledResourceIterator& currentIterator, const float& timeStep, const Vector4F& cameraPosition, void*& mappedResource);
	void ComputeAndRenderDX12Sorted(Particle_PooledResourceIterator& currentIterator, const float& timeStep, const Vector4F& cameraPosition, PriorityQueueArray<Particle*, float>& mappedResource);

	void ReleaseAllParticles(Particle_PooledResourceIterator& currentIterator, Particle_PooledResourcePool& particlePool);

	const ParticleName& GetParticleName() const;
	const int GetNumberOfParticles() const;

private:
	Particle_PooledResourceList activeParticles;
	ParticleName particleName;
};
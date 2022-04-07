#include "ParticleBurst.h"

#include "Particle_PooledResourcePool.h"
#include "../Model/Managers/TextureManager.h"
#include "../Model/Managers/ModelManager.h"

#include "ParticleBurstData.h"

#include "../../../Expedition Resources/EngineSettings.h"

void ParticleBurst::Initialize(const ParticleBurstData& burstData)
{
	particleName = burstData.particleName;
}

void ParticleBurst::AssignParticle(Particle_PooledResourceIterator& currentIterator)
{
	activeParticles.PushBack(currentIterator);
}


void ParticleBurst::ComputeAndRenderDX12(Particle_PooledResourceIterator& currentIterator, const float& timeStep, const Vector4F& cameraPosition, void*& mappedResource)
{
	activeParticles.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		currentIterator.GetCurrentParticle().ComputeDX12(timeStep, cameraPosition);
		currentIterator.GetCurrentParticle().RenderDX12(mappedResource);
		mappedResource = (char*)mappedResource + sizeof(GO_DataGPU_Particle);
		++currentIterator;
	}
}

void ParticleBurst::ComputeAndRenderDX12Sorted(Particle_PooledResourceIterator& currentIterator, const float& timeStep, const Vector4F& cameraPosition, PriorityQueueArray<Particle*, float>& mappedResource)
{
	activeParticles.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		currentIterator.GetCurrentParticle().ComputeDX12(timeStep, cameraPosition);

		mappedResource.Push(-currentIterator.GetCurrentParticle().distFromCamSqr, &currentIterator.GetCurrentParticle());
		
		++currentIterator;
	}
}

void ParticleBurst::ReleaseAllParticles(Particle_PooledResourceIterator& currentIterator, Particle_PooledResourcePool& particlePool)
{
	while (activeParticles.GetSize() > 0)
	{
		activeParticles.PopFront(currentIterator);
		particlePool.ReleaseResource(currentIterator);
	}
}

const ParticleName& ParticleBurst::GetParticleName() const
{
	return particleName;
}

const int ParticleBurst::GetNumberOfParticles() const
{
	return activeParticles.GetSize();
}

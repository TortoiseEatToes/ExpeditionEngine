#include "Particle_PooledResourceIterator.h"

Particle_PooledResourceIterator::Particle_PooledResourceIterator(const Particle_PooledResourceIterator& other)
{
	pResource = other.pResource;
}

Particle_PooledResourceIterator& Particle_PooledResourceIterator::operator=(const Particle_PooledResourceIterator& other)
{
	if (&other != this)
	{
		pResource = other.pResource;
	}
	return *this;
}

Particle_PooledResourceIterator& Particle_PooledResourceIterator::operator++()
{
	pResource = pResource->pNext;
	return *this;
}

Particle_PooledResourceIterator& Particle_PooledResourceIterator::operator--()
{
	pResource = pResource->pPrevious;
	return *this;
}

Particle& Particle_PooledResourceIterator::GetCurrentParticle()
{
	return pResource->particle;
}

void Particle_PooledResourceIterator::SetResource(Particle_PooledResource& resource)
{
	pResource = &resource;
}

void Particle_PooledResourceIterator::SetResource(Particle_PooledResource*& resource)
{
	pResource = resource;
}

Particle_PooledResource*& Particle_PooledResourceIterator::GetResource()
{
	return pResource;
}

bool Particle_PooledResourceIterator::IsAtEnd() const
{
	return pResource->pNext == nullptr;
}

bool Particle_PooledResourceIterator::IsOutOfNodes() const
{
	return pResource == nullptr;
}

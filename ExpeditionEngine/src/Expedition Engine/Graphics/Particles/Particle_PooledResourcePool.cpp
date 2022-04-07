#include "Particle_PooledResourcePool.h"

#include <assert.h>

Particle_PooledResourcePool::Particle_PooledResourcePool()
{
	//Push all of the resources from the array into the stack
	Particle_PooledResource* pCurrentResource = &resourcePool[0];
	int counter = 0;
	while (counter < NumberOfParticles)
	{
		unusedResourceStack.Push(pCurrentResource);
		++pCurrentResource;
		++counter;
	}
}

Particle_PooledResourcePool::~Particle_PooledResourcePool()
{
	assert(unusedResourceStack.GetSize() == NumberOfParticles && "NOT ALL PARTICLES WERE RETURNED TO THE POOL");
}

void Particle_PooledResourcePool::AcquireResource(Particle_PooledResourceIterator& iterator)
{
	assert(unusedResourceStack.GetSize() > 0);
	unusedResourceStack.Pop(iterator);
}

void Particle_PooledResourcePool::ReleaseResource(Particle_PooledResourceIterator& iterator)
{
	assert(iterator.GetResource()->pNext == nullptr && iterator.GetResource()->pPrevious == nullptr);
	unusedResourceStack.Push(iterator);
}

const int& Particle_PooledResourcePool::GetNumberOfAvailableResources() const
{
	return unusedResourceStack.GetSize();
}

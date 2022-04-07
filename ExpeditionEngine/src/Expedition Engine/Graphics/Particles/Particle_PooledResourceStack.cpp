#include "Particle_PooledResourceStack.h"

#include <assert.h>

void Particle_PooledResourceStack::Push(Particle_PooledResource*& resource)
{
	assert(resource->pNext == nullptr && resource->pPrevious == nullptr);
	resource->pNext = pFront;
	pFront = resource;
	++size;
}

void Particle_PooledResourceStack::Push(Particle_PooledResourceIterator& iterator)
{
	assert(iterator.GetResource()->pNext == nullptr && iterator.GetResource()->pPrevious == nullptr);
	iterator.GetResource()->pNext = pFront;
	pFront = iterator.GetResource();
	++size;
}

void Particle_PooledResourceStack::Pop(Particle_PooledResourceIterator& iterator)
{
	assert(size > 0);

	iterator.SetResource(*pFront);
	pFront = pFront->pNext;

	//Sanitize the nodes before they leave the stack just in case
	iterator.GetResource()->pNext = nullptr;
	--size;
}

const int& Particle_PooledResourceStack::GetSize() const
{
	return size;
}
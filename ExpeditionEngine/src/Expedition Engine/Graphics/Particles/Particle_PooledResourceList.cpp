#include "Particle_PooledResourceList.h"

#include <assert.h>

Particle_PooledResourceList::~Particle_PooledResourceList()
{
	assert(size == 0);
}

void Particle_PooledResourceList::SetFront(Particle_PooledResourceIterator& outIterator)
{
	outIterator.SetResource(pFront);
}

void Particle_PooledResourceList::SetBack(Particle_PooledResourceIterator& outIterator)
{
	outIterator.SetResource(pBack);
}

void Particle_PooledResourceList::PushFront(Particle_PooledResourceIterator& iterator)
{
	assert(iterator.GetResource()->pNext == nullptr && iterator.GetResource()->pPrevious == nullptr);
	if (pFront == nullptr)
	{
		pFront = iterator.GetResource();
		pBack = pFront;
	}
	else
	{
		pFront->pPrevious = iterator.GetResource();
		pFront->pPrevious->pNext = pFront;
		pFront = pFront->pPrevious;
	}
	++size;
}

void Particle_PooledResourceList::PushBack(Particle_PooledResourceIterator& iterator)
{
	assert(iterator.GetResource()->pNext == nullptr && iterator.GetResource()->pPrevious == nullptr);
	if (pBack == nullptr)
	{
		pBack = iterator.GetResource();
		pFront = pBack;
	}
	else
	{
		pBack->pNext = iterator.GetResource();
		pBack->pNext->pPrevious = pBack;
		pBack = pBack->pNext;
	}
	++size;
}

void Particle_PooledResourceList::PopFront(Particle_PooledResourceIterator& iterator)
{
	assert(size > 0);
	iterator.SetResource(*pFront);

	if (size >= 2)
	{
		pFront = pFront->pNext;
		pFront->pPrevious = nullptr;
	}
	else //size is 1
	{
		pFront = nullptr;
		pBack = nullptr;
	}

	SanitizeResource(iterator.GetResource());
	--size;
}

void Particle_PooledResourceList::PopBack(Particle_PooledResourceIterator& iterator)
{
	assert(size > 0);
	iterator.SetResource(*pBack);

	if (size >= 2)
	{
		pBack = pBack->pPrevious;
		pBack->pNext = nullptr;
	}
	else // size is 1
	{
		pFront = nullptr;
		pBack = nullptr;
	}

	SanitizeResource(iterator.GetResource());
	--size;
}

void Particle_PooledResourceList::Remove(Particle_PooledResourceIterator& iterator)
{
	assert(size > 0);

	if (iterator.GetResource()->pPrevious == nullptr)
	{
		if (iterator.GetResource()->pNext == nullptr)
		{
			//It is the only node
			pFront = nullptr;
			pBack = nullptr;
		}
		else
		{
			//It is the front node
			pFront->pNext->pPrevious = nullptr;
			pFront = pFront->pNext;
		}
	}
	else if (iterator.GetResource()->pNext == nullptr)
	{
		//We know that is the back node
		pBack->pPrevious->pNext = nullptr;
		pBack = pBack->pPrevious;
	}
	else
	{
		//It is in the middle of the list
		iterator.GetResource()->pPrevious->pNext = iterator.GetResource()->pNext;
		iterator.GetResource()->pNext->pPrevious = iterator.GetResource()->pPrevious;
	}

	SanitizeResource(iterator.GetResource());
	--size;
}

const int& Particle_PooledResourceList::GetSize() const
{
	return size;
}

void Particle_PooledResourceList::SanitizeResource(Particle_PooledResource*& resource)
{
	resource->pNext = nullptr;
	resource->pPrevious = nullptr;
}
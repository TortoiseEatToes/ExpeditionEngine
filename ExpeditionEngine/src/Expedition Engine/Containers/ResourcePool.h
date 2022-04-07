#pragma once

#include "Stack.h"
#include "Stack_PooledResource.h"
#include "../Engine/EngineUtilities.h"

template <typename T>
class ResourcePool
{
public:
	ResourcePool() = delete;
	ResourcePool(const int& sizeOfArrays)
	{
		arraySize = sizeOfArrays;
		CreateNewResourceArray();
	}
	ResourcePool(const ResourcePool&) = delete;
	ResourcePool& operator= (const ResourcePool&) = delete;
	~ResourcePool()
	{
		while (resourceArrays.GetSize() > 0)
		{
			delete[] resourceArrays.Pop();
		}
	}

	void AcquireResource(PooledResourceIterator<T>& iterator)
	{
		if (unusedResourceStack.GetSize() == 0)
		{
			EngineUtilities::LogWarning("Allocating new pooled resource");
			CreateNewResourceArray();
		}
		unusedResourceStack.Pop(iterator);
	}

	void ReleaseResource(PooledResourceIterator<T>& iterator)
	{
		assert(iterator.IsResourceInUse());
		unusedResourceStack.Push(iterator);
	}

	const int& GetNumberOfAvailableResources() const
	{
		return unusedResourceStack.GetSize();
	}

private:
	void CreateNewResourceArray()
	{
		PooledResource<T>* pCurrentResource = new PooledResource<T>[arraySize];
		resourceArrays.Push(pCurrentResource);

		int counter = 0;
		while (counter < arraySize)
		{
			unusedResourceStack.Push(pCurrentResource);
			++pCurrentResource;
			++counter;
		}
	}

	Stack_PooledResource<T> unusedResourceStack;
	Stack<PooledResource<T>*> resourceArrays;

	int arraySize = -1;
};

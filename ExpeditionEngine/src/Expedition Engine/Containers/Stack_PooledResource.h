#pragma once

#include "PooledResourceIterator.h"

#include <assert.h>

template <typename T>
class Stack_PooledResource
{
public:
	Stack_PooledResource() = default;
	Stack_PooledResource(const Stack_PooledResource&) = delete;
	Stack_PooledResource& operator= (const Stack_PooledResource&) = delete;
	~Stack_PooledResource()
	{
		//assert(size == 0);
	}

	void Push(PooledResourceIterator<T>& iterator)
	{
		assert(iterator.GetResource()->pNext == nullptr && iterator.GetResource()->pPrevious == nullptr);
		iterator.GetResource()->pNext = pFront;
		pFront = iterator.GetResource();
		++size;
	}

	void Push(PooledResource<T>*& resource)
	{
		assert(resource->pNext == nullptr && resource->pPrevious == nullptr);
		resource->pNext = pFront;
		pFront = resource;
		++size;
	}

	void Pop(PooledResourceIterator<T>& iterator)
	{
		assert(size > 0);

		iterator.SetResource(*pFront);
		pFront = pFront->pNext;

		//Sanitize the nodes before they leave the stack just in case
		iterator.GetResource()->pNext = nullptr;
		--size;
	}

	/// <summary>Get the number of objects currently in the stack.</summary>
	/// <returns>const int reference to the size of the stack</returns> 
	const int& GetSize() const
	{
		return size;
	}

private:
	PooledResource<T>* pFront = nullptr;
	int size = 0;
};
#pragma once

#include "PooledResourceIterator.h"

#include <assert.h>

template <typename T>
class Queue_PooledResource
{
public:
	Queue_PooledResource() = default;
	Queue_PooledResource(const Queue_PooledResource&) = delete;
	Queue_PooledResource& operator= (const Queue_PooledResource&) = delete;
	~Queue_PooledResource()
	{
		assert(size == 0);
	}

	void Push(PooledResourceIterator<T>& iterator)
	{
		assert(iterator.GetResource()->pNext == nullptr && iterator.GetResource()->pPrevious == nullptr);

		if (pBack != nullptr)
		{
			pBack->pNext = iterator.GetResource();
			pBack = iterator.GetResource();
		}
		else
		{
			pFront = iterator.GetResource();
			pBack = iterator.GetResource();
		}

		++size;
	}

	void Pop(PooledResourceIterator<T>& iterator)
	{
		assert(size > 0);

		iterator.SetResource(pFront);

		if (size > 1)
		{
			pFront = pFront->pNext;
		}
		else
		{
			pFront = nullptr;
			pBack = nullptr;
		}

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
	PooledResource<T>* pBack = nullptr;
	int size = 0;
};
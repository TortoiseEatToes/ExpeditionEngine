#pragma once

#include "PooledResourceIterator.h"

#include <assert.h>

template <typename T>
class List_PooledResource
{
public:
	List_PooledResource() = default;
	List_PooledResource(const List_PooledResource& other) = delete;
	List_PooledResource& operator= (const List_PooledResource& other) = delete;
	~List_PooledResource()
	{
		assert(size == 0);
	}

	void SetFront(PooledResourceIterator<T>& outIterator)
	{
		outIterator.SetResource(*pFront);
	}

	void SetBack(PooledResourceIterator<T>& outIterator)
	{
		outIterator.SetResource(*pBack);
	}

	void PushFront(PooledResourceIterator<T>& iterator)
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

	void PushBack(PooledResourceIterator<T>& iterator)
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


	void PopFront(PooledResourceIterator<T>& iterator)
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
	void PopBack(PooledResourceIterator<T>& iterator)
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

	void Remove(PooledResourceIterator<T>& iterator)
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

	const int GetSize() const
	{
		return size;
	}

	void SanitizeResource(PooledResource<T>*& resource)
	{
		resource->pNext = nullptr;
		resource->pPrevious = nullptr;
	}

private:
	PooledResource<T>* pFront = nullptr;
	PooledResource<T>* pBack = nullptr;
	int size = 0;
};
#pragma once

#include "PooledResource.h"

template <typename T>
class PooledResourceIterator
{
public:
	PooledResourceIterator() = default;
	PooledResourceIterator(const PooledResourceIterator& other)
	{
		pResource = other.pResource;
	}
	PooledResourceIterator& operator= (const PooledResourceIterator& other)
	{
		if (&other != this)
		{
			pResource = other.pResource;
		}
		return *this;
	}
	~PooledResourceIterator() = default;

	PooledResourceIterator& operator++()
	{
		pResource = pResource->pNext;
		return *this;
	}
	PooledResourceIterator& operator--()
	{
		pResource = pResource->pPrevious;
		return *this;
	}

	T& GetCurrentObject() const
	{
		return pResource->object;
	}

	bool IsAtEnd() const
	{
		return pResource->pNext == nullptr;
	}

	bool IsOutOfNodes() const
	{
		return pResource == nullptr;
	}

	bool IsResourceInUse() const
	{
		return pResource->pNext == nullptr && pResource->pPrevious == nullptr;
	}

	//void GetNext(PooledResourceIterator& otherIterator)
	//{
	//	otherIterator.pResource = pResource->pNext;
	//}

	void SetResource(PooledResource<T>& resource)
	{
		pResource = &resource;
	}

	void SetResource(PooledResource<T>* resource)
	{
		pResource = resource;
	}

	PooledResource<T>*& GetResource()
	{
		return pResource;
	}

private:
	PooledResource<T>* pResource;
};
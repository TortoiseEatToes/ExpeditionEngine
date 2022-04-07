#pragma once

#include "../Math/Base/Align16.h"

template <typename T>
class PooledResource : public Align16
{
public:
	PooledResource() = default;
	PooledResource(const PooledResource& other) = default;
	PooledResource& operator= (const PooledResource&) = delete;
	~PooledResource() = default;

	T object;
	PooledResource<T>* pNext = nullptr;
	PooledResource<T>* pPrevious = nullptr;
};
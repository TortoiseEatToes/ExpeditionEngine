#pragma once

template <typename T>
struct PoolFixedSizeBlock
{
public:
	T object;
	PoolFixedSizeBlock* pNext = nullptr;
	PoolFixedSizeBlock* pPrevious = nullptr;
};
#pragma once

#include "PoolFixedSizeBlock.h"

template <typename T>
class PoolFixedSize
{
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(const Iterator& other)
		{
			pCurrentBlock = other.pCurrentBlock;
		}
		Iterator& operator= (const Iterator& other)
		{
			if (&other != this)
			{
				pCurrentBlock = other.pCurrentBlock;
			}
			return *this;
		}
		~Iterator() = default;

		T& GetCurrentObject()
		{
			return pCurrentBlock->objectInstance;
		}

	private: 
		//friend class PoolArray;
		//
		//void SetNode(const NodeDoublyLinked<T>* otherNode)
		//{
		//	currentNode = otherNode;
		//}

		PoolFixedSizeBlock* pCurrentBlock;
	};

	PoolFixedSize() = delete;
	PoolFixedSize(const int pooledObjects)
	{
		size = pooledObjects;
		pBlockPool = new PoolFixedSizeBlock<T>[size];

		//When you first create this pool, link all of the headers up to their corresponding object instances and then chain the headers together into the unused list
		int counter = 0;
		NodeDoublyLinked<T>* pCurrentNode = &headerPool[0];

		pCurrentNode.pNext = headerPool[1];
		//Leave previous as nullptr

		while (counter < size - 1)
		{
			pCurrentNode = &headerPool[counter];
			pCurrentNode.objectInstance = &objectPool[counter];
			pCurrentNode.pPrevious = &headerPool[counter];
			pCurrentNode.pNext = &headerPool[++counter];
		}

		pCurrentNode = &headerPool[counter];
		pCurrentNode.objectInstance = &objectPool[counter];
		//Leave next as nullptr
		pCurrentNode.pPrevious = &headerPool[counter];
	}
	PoolFixedSize(const PoolFixedSize&) = delete;
	PoolFixedSize& operator= (const PoolFixedSize&) = delete;
	~PoolFixedSize()
	{
		delete[] pBlockPool;
	}

	int GetSize()
	{
		return size;
	}

private:
	PoolFixedSizeBlock<T>* pBlockPool = nullptr;
	PoolFixedSizeBlock<T>* pHeadFreeBlocks = nullptr;
	PoolFixedSizeBlock<T>* pHeadUsedBlocks = nullptr;
	int size = -1;
};
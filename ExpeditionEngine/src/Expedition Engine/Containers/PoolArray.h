#ifndef POOLARRAY
#define POOLARRAY

#include "NodeDoublyLinked.h"

template <typename T>
class PoolArray
{
public:
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(const Iterator& other)
		{
			currentNode = other.currentNode;
		}
		Iterator& operator= (const Iterator& other)
		{
			if (&other != this)
			{
				currentNode = other.currentNode;
			}
			return *this;
		}
		~Iterator() = default;
		T& GetCurrentObject()
		{
			return *currentNode->objectInstance;
		}

	private:
		friend class PoolArray;

		void SetNode(const NodeDoublyLinked<T>* otherNode)
		{
			currentNode = otherNode;
		}

		NodeDoublyLinked<T>* currentNode;
	};

	PoolArray() = delete;
	PoolArray(const int pooledObjects)
	{
		size = pooledObjects;
		objectPool = new T[size];
		headerPool = new NodeDoublyLinked<T>[size];

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
	PoolArray(const PoolArray&) = delete;
	PoolArray& operator= (const PoolArray&) = delete;
	~PoolArray()
	{
		delete[] objectPool;
		delete[] headerPool;
	}

	
	void GetPooledObject(PoolArray<T>::Iterator& outIterator)
	{
		assert(pooledNodesHead != nullptr);

		outIterator.SetNode(pooledNodesHead);

		usedNodesHead->pPrevious = pooledNodesHead;
		usedNodesHead = usedNodesHead->pPrevious;

		pooledNodesHead->pNext->pPrevious = nullptr;
		pooledNodesHead = pooledNodesHead->pNext;
	}

	void RecycleObject(PoolArray<T>::Iterator& iteratorToRecycle)
	{
		if (iteratorToRecycle.currentNode->pPrevious == nullptr)
		{
			if (iteratorToRecycle.currentNode->pNext == nullptr)
			{
				usedNodesHead = nullptr;

				pooledNodesHead->pPrevious = iteratorToRecycle.currentNode;
				iteratorToRecycle.currentNode->pNext = pooledNodesHead;
				pooledNodesHead = iteratorToRecycle.currentNode;
			}
			else
			{
				//It is the front node
				iteratorToRecycle.currentNode->pNext->pPrevious = nullptr;
				iteratorToRecycle.currentNode = iteratorToRecycle.currentNode->pNext;

				pooledNodesHead->pPrevious = iteratorToRecycle.currentNode;
				iteratorToRecycle.currentNode->pNext = pooledNodesHead;
				pooledNodesHead = iteratorToRecycle.currentNode;
			}
		}
		else if (iteratorToRecycle.currentNode->pNext == nullptr)
		{
			//We know that is the back node
			iteratorToRecycle.currentNode->pPrevious->pNext = nullptr;
			iteratorToRecycle.currentNode = iteratorToRecycle.currentNode->pPrevious;

			pooledNodesHead->pPrevious = iteratorToRecycle.currentNode;
			iteratorToRecycle.currentNode->pNext = pooledNodesHead;
			iteratorToRecycle.currentNode->pPrevious = nullptr;
			pooledNodesHead = iteratorToRecycle.currentNode;
		}
		else
		{
			//It is in the middle of the list
			iteratorToRecycle.currentNode->pPrevious->pNext = iteratorToRecycle.currentNode->pNext;
			iteratorToRecycle.currentNode->pNext->pPrevious = iteratorToRecycle.currentNode->pPrevious;

			pooledNodesHead->pPrevious = iteratorToRecycle.currentNode;
			iteratorToRecycle.currentNode->pNext = pooledNodesHead;
			iteratorToRecycle.currentNode->pPrevious = nullptr;
			pooledNodesHead = iteratorToRecycle.currentNode;
		}
	}

	/// <summary>Get the number of objects currently stored in the pool.</summary>
	/// <returns>int size of the pool</returns> 
	int GetSize() const
	{
		return size;
	}
	

private:
	NodeDoublyLinked<T>* headerPool;
	NodeDoublyLinked<T>* pooledNodesHead;
	NodeDoublyLinked<T>* usedNodesHead;
	T* objectPool;
	int size = -1;
};

#endif // !POOLARRAY

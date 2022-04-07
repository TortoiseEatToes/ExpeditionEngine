#ifndef Queue_H
#define Queue_H

#include "PoolSinglyLinkedNodes.h"

#include <assert.h>

//Templatized queue using singly linked nodes
template <typename T>
class Queue
{
public:
	Queue() = default;
	Queue(const Queue&) = delete;
	Queue& operator= (const Queue&) = delete;
	~Queue()
	{
		while (size > 0)
		{
			Pop();
		}
	}

	/// <summary>Push one object of the given type into the back of the queue.</summary>
	/// <param name="object">Reference to the object to push into the queue</param>
	void Push(const T& object)
	{
		NodeSinglyLinked<T>* pTempNode = nodePool.GetNode();
		pTempNode->objectInstance = object;

		if (pBack != nullptr)
		{
			pBack->pNext = pTempNode;
			pBack = pTempNode;
		}
		else
		{
			pBack = pTempNode;
			pFront = pTempNode;
		}
		++size;
	}

	/// <summary>Pop one object of the givent type off of the front of the queue.</summary>
	/// <returns>Reference to the object that was popped from the queue </returns> 
	T Pop()
	{
		assert(size > 0);

		NodeSinglyLinked<T>* pTempNode = pFront;
		T tempObject = pTempNode->objectInstance;

		if (size > 1)
		{
			pFront = pFront->pNext;
		}
		else
		{
			pFront = nullptr;
			pBack = nullptr;
		}

		--size;
		nodePool.RecycleNode(pTempNode);

		return tempObject;
	}

	/// <summary>Get the number of objects currently in the queue.</summary>
	/// <returns>const reference to the integer size of the queue </returns> 
	const int GetSize() const
	{
		return size;
	}

private:
	PoolSinglyLinkedNodes<T> nodePool;
	NodeSinglyLinked<T>* pFront = nullptr;
	NodeSinglyLinked<T>* pBack = nullptr;
	int size = 0;
};

#endif // !Queue_H
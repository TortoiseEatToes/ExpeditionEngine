#ifndef STACK_H
#define STACK_H

#include "PoolSinglyLinkedNodes.h"
#include <assert.h>

//Templatized stack using singly linked nodes
template <typename T>
class Stack
{
public:
	Stack() = default;
	Stack(const Stack&) = delete;
	Stack& operator= (const Stack&) = delete;
	~Stack()
	{
		while (size > 0)
		{
			Pop();
		}
	}

	/// <summary>Push one item onto the front of the stack.</summary>
	/// <param name="object">Reference to the object to push into the stack</param>
	void Push(const T& object)
	{
		NodeSinglyLinked<T>* pTempNode = nodePool.GetNode();
		pTempNode->objectInstance = object;

		pTempNode->pNext = pFront;
		pFront = pTempNode;
		++size;
	}

	/// <summary>Pop one item off of the front of the stack.</summary>
	/// <returns>reference to the object that was popped out of the stack</returns> 
	T Pop()
	{
		assert(size > 0);
		T tempObject = pFront->objectInstance;
		NodeSinglyLinked<T>* pTempNode = pFront;

		pFront = pFront->pNext;
		nodePool.RecycleNode(pTempNode);
		--size;
		
		return tempObject;
	}

	/// <summary>Peak at the item currently on top of the stack.</summary>
	/// <returns>reference to the object that is currently on top of the stack</returns> 
	T Peak()
	{
		assert(size > 0);
		return pFront->objectInstance;
	}

	/// <summary>Get the number of objects currently in the stack.</summary>
	/// <returns>const int reference to the size of the stack</returns> 
	int GetSize() const
	{
		return size;
	}

private:
	PoolSinglyLinkedNodes<T> nodePool;
	NodeSinglyLinked<T>* pFront = nullptr;
	int size = 0;
};

#endif // !Stack_H
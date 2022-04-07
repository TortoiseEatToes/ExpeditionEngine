#ifndef LIST_H
#define LIST_H

#include "PoolDoublyLinkedNodes.h"

#include <assert.h>

template <typename T>
class List
{
public:
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(const Iterator& other)
		{
			pCurrentNode = other.pCurrentNode;
		}
		Iterator& operator= (const Iterator& other)
		{
			if (&other != this)
			{
				pCurrentNode = other.pCurrentNode;
			}
			return *this;
		}
		~Iterator() = default;

		Iterator& operator++()
		{
			pCurrentNode = pCurrentNode->pNext;
			return *this;
		}
		Iterator& operator--()
		{
			pCurrentNode = pCurrentNode->pPrevious;
			return *this;
		}

		T& GetCurrentObject()
		{
			return pCurrentNode->objectInstance;
		}

		bool IsAtEnd()
		{
			return pCurrentNode->pNext == nullptr;
		}

		bool IsOutOfNodes()
		{
			return pCurrentNode == nullptr;
		}

		void GetNext(Iterator& otherIterator)
		{
			otherIterator.pCurrentNode = pCurrentNode->pNext;
		}

	private:
		friend class List;

		void SetNode(NodeDoublyLinked<T>* pOtherNode)
		{
			pCurrentNode = pOtherNode;
		}
		NodeDoublyLinked<T>* pCurrentNode = nullptr;
	};


	List() = default;
	List(const List& other)
	{
		List<T>::Iterator iterator;

		other.SetFront(iterator);

		while (!iterator.IsOutOfNodes())
		{
			PushFront(iterator.GetObject());
			iterator++;
		}
	}
	List& operator= (const List& other)
	{
		if (&other != this)
		{
			List<T>::Iterator iterator;

			other.SetFront(iterator);

			while (!iterator.IsOutOfNodes())
			{
				PushFront(iterator.GetObject());
				iterator++;
			}
		}
		return *this;
	}
	~List()
	{
		Clear();
	}

	/// <summary>Set the iterator to point to the front of the list.</summary>
	void SetFront(List<T>::Iterator& outIterator)
	{
		outIterator.SetNode(pFront);
	}

	/// <summary>Set the iterator to point to the back of the list.</summary>
	void SetBack(List<T>::Iterator& outIterator)
	{
		outIterator.pCurrentNode = pBack;
	}

	/// <summary>Push the new resource into the front of the list.</summary>
	void PushFront(const T& object)
	{
		if (pFront == nullptr)
		{
			pFront = nodePool.GetNode();
			pBack = pFront;
		}
		else
		{
			pFront->pPrevious = nodePool.GetNode();
			pFront->pPrevious->pNext = pFront;
			pFront = pFront->pPrevious;
		}

		pFront->objectInstance = object;
		++size;
	}

	/// <summary>Push the new resource into the front of the list.</summary>
	void PushFront(const T& object, List<T>::Iterator& outIterator)
	{
		if (pFront == nullptr)
		{
			pFront = nodePool.GetNode();
			pBack = pFront;
		}
		else
		{
			pFront->pPrevious = nodePool.GetNode();
			pFront->pPrevious->pNext = pFront;
			pFront = pFront->pPrevious;
		}

		pFront->objectInstance = object;
		outIterator.pCurrentNode = pFront;
		++size;
	}

	/// <summary>Push the new resource into the back of the list.</summary>
	void PushBack(const T& object)
	{
		if (pBack == nullptr)
		{
			pBack = nodePool.GetNode();
			pFront = pBack;
		}
		else
		{
			pBack->pNext = nodePool.GetNode();
			pBack->pNext->pPrevious = pBack;
			pBack = pBack->pNext;
		}

		pBack->objectInstance = object;
		++size;
	}

	/// <summary>Push the new resource into the back of the list.</summary>
	void PushBack(const T& object, List<T>::Iterator& outIterator)
	{
		if (pBack == nullptr)
		{
			pBack = nodePool.GetNode();
			pFront = pBack;
		}
		else
		{
			pBack->pNext = nodePool.GetNode();
			pBack->pNext->pPrevious = pBack;
			pBack = pBack->pNext;
		}

		pBack->objectInstance = object;
		outIterator.pCurrentNode = pBack;
		++size;
	}

	/// <summary>Removes the item at the front of the list.</summary>
	T PopFront()
	{
		assert(size > 0);
		T tempObject = pFront->objectInstance;

		if (size >= 2)
		{
			pFront = pFront->pNext;
			nodePool.RecycleNode(pFront->pPrevious);
			pFront->pPrevious = nullptr;
		}
		else //size is 1
		{
			nodePool.RecycleNode(pFront);
			pFront = nullptr;
			pBack = nullptr;
		}

		--size;
		return tempObject;
	}

	/// <summary>Removes the item at the back of the list.</summary>
	T PopBack()
	{
		assert(size > 0);
		T tempObject = pBack->objectInstance;

		if (size >= 2)
		{
			pBack = pBack->pPrevious;
			nodePool.RecycleNode(pBack->pNext);
			pBack->pNext = nullptr;
		}
		else // size is 1
		{
			nodePool.RecycleNode(pBack);
			pFront = nullptr;
			pBack = nullptr;
		}

		--size;
		return tempObject;
	}

	/// <summary>Attempts to find an instance of the object stored in the list.</summary>
	/// <returns>Returns true if the object is in the list, false otherwise</returns> 
	bool Contains(const T& object)
	{
		SetFront(iterator);
		while (!iterator.IsOutOfNodes())
		{
			if (iterator.GetCurrentObject() == object)
			{
				return true;
			}
			++iterator;
		}
		return false;
	}

	/// <summary>Attempts to find the first instance of the object stored in the list and make the outIterator point to it.</summary>
	/// <returns>Returns true if the object is in the list, false otherwise</returns> 
	bool Contains(const T& object, Iterator& outIterator)
	{
		SetFront(outIterator);
		while (!outIterator.IsOutOfNodes())
		{
			if (outIterator.GetCurrentObject() == object)
			{
				return true;
			}
			++outIterator;
		}
		return false;
	}

	/// <summary>Removes the first instance of the object from the list if possible.</summary>
	/// <returns>Returns true if there was an object to remove or false if there wasn't anything.</returns> 
	bool Remove(const T& object)
	{
		if (Contains(object, iterator))
		{
			Remove(iterator.pCurrentNode);
			return true;
		}
		else
		{
			return false;
		}
	}

	/// <summary>Removes the object from the list.</summary>
	void Remove(List<T>::Iterator& iteratorToRemove)
	{
		assert(size > 0);
		assert(iteratorToRemove.pCurrentNode != nullptr);

		Remove(iteratorToRemove.pCurrentNode);
	}

	/// <summary>Get the current size of this list.</summary>
	const int& GetSize() const
	{
		return size;
	}

	/// <summary>Wipe all references stored in this list.</summary>
	void Clear()
	{
		while (pFront != nullptr)
		{
			PopFront();
		}
	}


private:
	void Remove(NodeDoublyLinked<T>* pNodeToRemove)
	{
		if (pNodeToRemove->pPrevious == nullptr)
		{
			if (pNodeToRemove->pNext == nullptr)
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
		else if (pNodeToRemove->pNext == nullptr)
		{
			//We know that is the back node
			pBack->pPrevious->pNext = nullptr;
			pBack = pBack->pPrevious;
		}
		else
		{
			//It is in the middle of the list
			pNodeToRemove->pPrevious->pNext = pNodeToRemove->pNext;
			pNodeToRemove->pNext->pPrevious = pNodeToRemove->pPrevious;
		}

		nodePool.RecycleNode(pNodeToRemove);
		--size;
	}

	PoolDoublyLinkedNodes<T> nodePool;
	NodeDoublyLinked<T>* pFront = nullptr;
	NodeDoublyLinked<T>* pBack = nullptr;
	Iterator iterator;
	int size = 0;
};

#endif // !LIST_H
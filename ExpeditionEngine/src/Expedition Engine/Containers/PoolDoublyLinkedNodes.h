#ifndef POOLDOUBLYLINKEDNODES_H
#define POOLDOUBLYLINKEDNODES_H

#include "NodeDoublyLinked.h"

template <typename T>
class PoolDoublyLinkedNodes
{
public:
	PoolDoublyLinkedNodes() = default;
	PoolDoublyLinkedNodes(const PoolDoublyLinkedNodes&) = delete;
	PoolDoublyLinkedNodes& operator= (const PoolDoublyLinkedNodes&) = delete;
	~PoolDoublyLinkedNodes() 
	{
		while (pHead != nullptr)
		{
			pTempNode = pHead->pNext;
			delete pHead;
			pHead = pTempNode;
		}
	}

	NodeDoublyLinked<T>* GetNode()
	{
		if (pHead != nullptr)
		{
			pTempNode = pHead;
			pHead = pHead->pNext;

			pTempNode->pNext = nullptr;
			pTempNode->pPrevious = nullptr;
		}
		else
		{
			pTempNode = new NodeDoublyLinked<T>();
		}

		return pTempNode;
	}

	void RecycleNode(NodeDoublyLinked<T>* pNodeToRecycle)
	{
		pNodeToRecycle->pPrevious = nullptr;

		if (pHead != nullptr)
		{
			pNodeToRecycle->pNext = pHead;
		}
		else
		{
			pNodeToRecycle->pNext = nullptr;
		}

		pHead = pNodeToRecycle;
	}

private:
	NodeDoublyLinked<T>* pHead = nullptr;
	NodeDoublyLinked<T>* pTempNode = nullptr;
};

#endif // !POOLDOUBLYLINKEDNODES_H
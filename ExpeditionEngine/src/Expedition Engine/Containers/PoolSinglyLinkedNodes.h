#ifndef POOLSINGLYLINKEDNODES_H
#define POOLSINGLYLINKEDNODES_H

#include "NodeSinglyLinked.h"

template <typename T>
class PoolSinglyLinkedNodes
{
public:
	PoolSinglyLinkedNodes() = default;
	PoolSinglyLinkedNodes(const PoolSinglyLinkedNodes&) = delete;
	PoolSinglyLinkedNodes& operator= (const PoolSinglyLinkedNodes&) = delete;
	~PoolSinglyLinkedNodes()
	{
		NodeSinglyLinked<T>* pTempNode = nullptr;
		while (pHead != nullptr)
		{
			pTempNode = pHead->pNext;
			delete pHead;
			pHead = pTempNode;
		}
	}

	NodeSinglyLinked<T>* GetNode()
	{
		NodeSinglyLinked<T>* pTempNode = nullptr;
		if (pHead != nullptr)
		{
			pTempNode = pHead;
			pHead = pHead->pNext;

			pTempNode->pNext = nullptr;
		}
		else
		{
			pTempNode = new NodeSinglyLinked<T>();
		}

		return pTempNode;
	}

	void RecycleNode(NodeSinglyLinked<T>* pNodeToRecycle)
	{
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
	NodeSinglyLinked<T>* pHead = nullptr;
};

#endif // !POOLSINGLYLINKEDNODES_H
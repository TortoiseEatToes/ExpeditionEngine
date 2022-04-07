#ifndef PRIORITYQUEUEARRAY
#define PRIORITYQUEUEARRAY

#include "MinHeapObject.h"
#include <assert.h>
#include <limits.h>

//MUST implement the operator> for TPriority
template <typename T, typename TPriority>
class PriorityQueueArray
{
public:
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(const Iterator& other)
		{
			pPriorityObject = other.pPriorityObject;
		}
		Iterator& operator= (const Iterator& other)
		{
			if (&other != this)
			{
				pPriorityObject = other.pPriorityObject;
			}
			return *this;
		}
		~Iterator() = default;

	private:
		friend class PriorityQueueArray;

		PriorityObject<T>* pPriorityObject = nullptr;
	};

	PriorityQueueArray() = delete;
	PriorityQueueArray(const int sizeOfQueue)
	{
		maxSize = sizeOfQueue; //There is a dead spot in the first index
		minHeap = new MinHeapObject<T, TPriority>[sizeOfQueue + 1];
		priorityData = new PriorityObject<T>[sizeOfQueue + 1];

		//Inserting them in inverse order makes the stack favor using the front of the array
		int counter = sizeOfQueue;
		while (counter > 0)
		{
			PushOntoNodeStack(&priorityData[counter]);
			--counter;
		}
	}
	PriorityQueueArray(const PriorityQueueArray& other) = delete;
	PriorityQueueArray& operator= (const PriorityQueueArray& other) = delete;
	~PriorityQueueArray()
	{
		delete[] minHeap;
		delete[] priorityData;
	}

	void Push(const int priorityLevel, const T& object, Iterator& iterator)
	{
		assert(currentSize < maxSize);

		iterator.pPriorityObject = PopFromNodeStack();

		++currentSize;
		PushNewElementToBackOfArray(priorityLevel, object, iterator.pPriorityObject);
		Swim(currentSize);
	}

	void Push(const TPriority& priorityLevel, const T& object)
	{
		assert(currentSize < maxSize);

		++currentSize;
		PushNewElementToBackOfArray(priorityLevel, object, PopFromNodeStack());
		Swim(currentSize);
	}

	void Pop(T& outObject)
	{
		assert(currentSize > 0);

		outObject = minHeap[1].pPriorityObject->currentObject;
		Swap(1, currentSize);
		PushOntoNodeStack(minHeap[currentSize].pPriorityObject);
		--currentSize;
		Sink(1);
	}

	void Remove(Iterator& iterator)
	{
		assert(currentSize > 0 && iterator.pPriorityObject != nullptr);
		int temp = iterator.pPriorityObject->indexOfMinHeapObject;
		Swap(temp, currentSize);
		PushOntoNodeStack(iterator.pPriorityObject);
		--currentSize;
		Sink(temp);

		iterator.pPriorityObject = nullptr;
	}

	T* PeekFront() const
	{
		assert(currentSize > 0);
		return minHeap[1].pPriorityObject->currentObject;
	}

	TPriority PeekFrontPriority() const
	{
		assert(currentSize > 0);
		return minHeap[1].priority;
	}

	int Size() const
	{
		return currentSize;
	}

	bool IsFull()
	{
		return currentSize == maxSize;
	}

private:
	bool IsLessThan(const int i, const int j)
	{
		return minHeap[i].priority > minHeap[j].priority;
	}

	void PushNewElementToBackOfArray(const TPriority& priorityLevel, const T& object, PriorityObject<T>* priorityObject)
	{
		minHeap[currentSize].priority = priorityLevel;
		minHeap[currentSize].pPriorityObject = priorityObject;

		priorityObject->currentObject = object;
		priorityObject->indexOfMinHeapObject = currentSize;
	}

	void Swap(const int& i, const int& j)
	{
		minHeap[i].pPriorityObject->indexOfMinHeapObject = j;
		minHeap[j].pPriorityObject->indexOfMinHeapObject = i;

		tempMinHeapObject = minHeap[i];
		minHeap[i] = minHeap[j];
		minHeap[j] = tempMinHeapObject;
	}

	void Sink(int k)
	{
		while (2 * k <= currentSize)
		{
			tempIndex = k * 2;
			if (tempIndex < currentSize && IsLessThan(tempIndex, tempIndex + 1))
			{
				++tempIndex;
			}
			if (!IsLessThan(k, tempIndex))
			{
				break;
			}
			Swap(k, tempIndex);
			k = tempIndex;
		}
	}

	void Swim(int k)
	{
		tempIndex = k;
		while (k > 1 && IsLessThan(k / 2, k))
		{
			Swap(k / 2, k);
			k = k / 2;
		}
	}

	void PushOntoNodeStack(PriorityObject<T>* node)
	{
		pTempNode = node;
		pTempNode->pNext = pUnusedNodesHead;
		pUnusedNodesHead = pTempNode;
	}
	PriorityObject<T>* PopFromNodeStack()
	{
		pTempNode = pUnusedNodesHead;
		pUnusedNodesHead = pUnusedNodesHead->pNext;
		return pTempNode;
	}

	MinHeapObject<T, TPriority> tempMinHeapObject;
	MinHeapObject<T, TPriority>* minHeap = nullptr;
	PriorityObject<T>* priorityData = nullptr;
	PriorityObject<T>* pUnusedNodesHead = nullptr;
	PriorityObject<T>* pTempNode = nullptr;
	int maxSize = -1;
	int currentSize = 0;
	int tempIndex;
};

#endif // !PRIORITYQUEUEARRAY
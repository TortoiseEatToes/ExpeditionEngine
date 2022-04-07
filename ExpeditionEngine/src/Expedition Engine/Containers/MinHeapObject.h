#ifndef MINHEAPOBJECT
#define MINHEAPOBJECT

#include "PriorityObject.h"

template <typename T, typename TPriority>
class MinHeapObject
{
public:
	MinHeapObject() = default;
	MinHeapObject(const MinHeapObject&) = delete;
	MinHeapObject& operator= (const MinHeapObject& other)
	{
		priority = other.priority;
		pPriorityObject = other.pPriorityObject;
		return *this;
	}
	~MinHeapObject() = default;

	TPriority priority;
	PriorityObject<T>* pPriorityObject = nullptr;
};

#endif // !MINHEAPOBJECT
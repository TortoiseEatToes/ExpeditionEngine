#ifndef PRIORITYOBJECT
#define PRIORITYOBJECT

template <typename T>
class PriorityObject
{
public:
	PriorityObject() = default;
	PriorityObject(const PriorityObject&) = delete;
	PriorityObject& operator= (const PriorityObject&) = delete;
	~PriorityObject() = default;

	T currentObject;
	int indexOfMinHeapObject = -1;
	PriorityObject* pNext = nullptr;
};

#endif // !PRIORITYOBJECT
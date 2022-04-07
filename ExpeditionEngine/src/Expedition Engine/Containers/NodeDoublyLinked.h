#ifndef NODEDOUBLYLINKED_H
#define NODEDOUBLYLINKED_H

template <typename T>
class NodeDoublyLinked
{
public:
	NodeDoublyLinked() = default;
	NodeDoublyLinked(const NodeDoublyLinked&) = delete;
	NodeDoublyLinked& operator= (const NodeDoublyLinked&) = delete;
	~NodeDoublyLinked() = default;


	T objectInstance;
	NodeDoublyLinked<T>* pNext = nullptr;
	NodeDoublyLinked<T>* pPrevious = nullptr;
};

#endif // !NODEDoublyLINKED_H
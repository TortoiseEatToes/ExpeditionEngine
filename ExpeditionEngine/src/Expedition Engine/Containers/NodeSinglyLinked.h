#ifndef NODESINGLYLINKED_H
#define NODESINGLYLINKED_H

template <typename T>
class NodeSinglyLinked
{
public:
	NodeSinglyLinked() = default;
	NodeSinglyLinked(const NodeSinglyLinked&) = delete;
	NodeSinglyLinked& operator= (const NodeSinglyLinked&) = delete;
	~NodeSinglyLinked() = default;


	T objectInstance;
	NodeSinglyLinked<T>* pNext = nullptr;
};

#endif // !NODESINGLYLINKED_H

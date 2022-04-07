#pragma once

#include <atomic>
#include <memory>

//THIS CLASS IS EXPERIMENTAL
//NO TOUCH

class T
{
	//Nothing
};

class Stack_ThreadSafe
{
private:

	struct Node
	{
		std::shared_ptr<T> data;
		Node* pNext;

		Node(T const& startingData):
			data(std::make_shared<T>(startingData))
		{
			//Do nothing
		}
	};
	
	std::atomic<Node*> pHead;

public:
	Stack_ThreadSafe() = default;
	Stack_ThreadSafe(const Stack_ThreadSafe&) = delete;
	Stack_ThreadSafe& operator= (const Stack_ThreadSafe&) = delete;
	~Stack_ThreadSafe() = default;


	void Push(T const& data)
	{
		Node* const newNode = new Node(data);
		newNode->pNext = pHead.load();
		while (!pHead.compare_exchange_weak(newNode->pNext, newNode));
	}

	std::shared_ptr<T> Pop()
	{
		Node* oldHead = pHead.load();

		while (oldHead && !pHead.compare_exchange_weak(oldHead, oldHead->pNext));

		return oldHead ? oldHead->data : std::shared_ptr<T>();
	}
};
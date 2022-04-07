#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H

#include "CircularData.h"

//
template <typename T>
class QueueArray
{
public:
	QueueArray() = delete;
	QueueArray(const int& sizeOfQueue)
		:front(size),
		back(size)
	{
		size = sizeOfQueue;
		data = new T*[size] {nullptr};
	}
	QueueArray(const QueueArray&) = delete;
	QueueArray& operator= (const QueueArray&) = delete;
	~QueueArray()
	{
		delete[] data;
	}


	bool Push(const T& value)
	{
		bool result = true;

		if (front != back || isEmpty)
		{
			data[back.GetIndex()] = value;
			++back;
			isEmpty = false;

			if (front == back)
			{
				isFull = true;
			}
		}
		else
		{
			result = false;
		}

		return result;
	}

	bool Pop(T& outValue)
	{
		bool result = true;

		if (front != back || isFull)
		{
			outValue = *data[front.GetIndex()];
			++front;
			isFull = false;

			if (front == back)
			{
				isEmpty = true;
			}
		}
		else
		{
			result = false;
		}

		return result;
	}

	bool GetIsEmpty() const
	{
		return isEmpty;
	}
	bool GetIsFull() const
	{
		return isFull;
	}

	const int size = -1;

private:
	CircularData front;
	CircularData back;

	T** data;

	bool isEmpty = true;
	bool isFull = false;
};

#endif // !QUEUEARRAY_H

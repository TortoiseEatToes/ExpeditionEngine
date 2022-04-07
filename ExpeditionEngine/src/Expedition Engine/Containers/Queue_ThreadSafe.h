#pragma once

//THIS CLASS IS EXPERIMENTAL
//NO TOUCH

class Queue_ThreadSafe
{
public:
	Queue_ThreadSafe() = default;
	Queue_ThreadSafe(const Queue_ThreadSafe&) = delete;
	Queue_ThreadSafe& operator= (const Queue_ThreadSafe&) = delete;
	~Queue_ThreadSafe() = default;

private:
};
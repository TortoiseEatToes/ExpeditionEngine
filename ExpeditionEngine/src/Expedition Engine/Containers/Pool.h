#ifndef POOL_H
#define POOL_H

#include "Stack.h"

#include <type_traits>

/// <summary>NOTE: THIS REQUIRES THAT THE GIVEN TYPE HAS A DEFAULT CONSTRUCTOR!!</summary>
template <typename T>
class Pool
{
public:
	Pool() = default;
	Pool(const int startingSize)
	{
		Create(startingSize);
	}
	Pool(const Pool&) = delete;
	Pool& operator= (const Pool&) = delete;
	~Pool()
	{
		DestroyAll();
	}

	/// <summary>Pop a pooled object out of the pool. NOTE: THIS REQUIRES THAT THE GIVEN TYPE HAS A DEFAULT CONSTRUCTOR!!</summary>
	/// <returns>return a reference an object that was popped from the pool</returns> 
	T* GetPooledObject()
	{
		const T* pTempObject = nullptr;

		if (pooledObjects.GetSize() > 0)
		{
			pTempObject = pooledObjects.Pop();
		}
		else
		{
			pTempObject = new T();
		}

		//HACK ALERT
		//This is a hack to remove the const qualifier so I can return this in a convenient form
		return const_cast<T*>(pTempObject);
	}

	/// <summary>Push an object that is no longer used into the pool.</summary>
	/// <param name="objectToPool">reference to the object to push into the pool</param>
	void RecycleObject(const T* const pObjectToPool)
	{
		pooledObjects.Push(pObjectToPool);
	}

	/// <summary>Get the number of objects currently stored in the pool.</summary>
	/// <returns>int the size of the pool</returns> 
	int GetSize() const
	{
		return pooledObjects.GetSize();
	}

	/// <summary>Destroy all of the objects currently in the pool.</summary>
	void DestroyAll()
	{
		while (pooledObjects.GetSize() > 0)
		{
			delete pooledObjects.Pop();
		}
	}

	/// <summary>Destroy nAmount number of objects if any exist.</summary>
	/// <param name="nAmount">const int nAmount number of objects to destroy</param>
	void Destroy(const int nAmount)
	{
		int i = 0;
		while (i < nAmount && pooledObjects.GetSize() > 0 )
		{
			delete pooledObjects.Pop();
			++i;
		}
	}

	/// <summary>Create nAmount number of objects and put them into the pool.</summary>
	/// <param name="nAmount">const int nAmount number of objects to create</param>
	void Create(const int nAmount)
	{
		for (int i = 0; i < nAmount; ++i)
		{
			pooledObjects.Push(new T());
		}
	}

private:
	Stack<const T*> pooledObjects;
};

#endif // !POOL_H

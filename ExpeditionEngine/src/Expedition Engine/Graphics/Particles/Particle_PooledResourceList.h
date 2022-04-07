#pragma once

#include "Particle_PooledResourceIterator.h"

//Used to make a doubly linked list out of Particle_PooledResource objects
class Particle_PooledResourceList
{
public:
	Particle_PooledResourceList() = default;
	Particle_PooledResourceList(const Particle_PooledResourceList& other) = delete;
	Particle_PooledResourceList& operator= (const Particle_PooledResourceList& other) = delete;
	~Particle_PooledResourceList();

	/// <summary>Set this iterator to point to the resource that is in the front of this list</summary>
	void SetFront(Particle_PooledResourceIterator& outIterator);

	/// <summary>Set this iterator to point to the resource that is in the back of this list</summary>
	void SetBack(Particle_PooledResourceIterator& outIterator);

	void PushFront(Particle_PooledResourceIterator& iterator);
	void PushBack(Particle_PooledResourceIterator& iterator);

	void PopFront(Particle_PooledResourceIterator& iterator);
	void PopBack(Particle_PooledResourceIterator& iterator);

	void Remove(Particle_PooledResourceIterator& iterator);

	///<summary> Get the number of particle resources currently in this list</summary>
	/// <returns>const reference to the int value of this list's current size</returns> 
	const int& GetSize() const;

private:
	void SanitizeResource(Particle_PooledResource*& resource);

	Particle_PooledResource* pFront = nullptr;
	Particle_PooledResource* pBack = nullptr;
	int size = 0;
};
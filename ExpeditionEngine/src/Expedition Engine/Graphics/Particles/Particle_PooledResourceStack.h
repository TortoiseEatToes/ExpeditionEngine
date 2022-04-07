#pragma once

#include "Particle_PooledResourceIterator.h"

//Used to make a stack out of Particle_PooledResource objects
class Particle_PooledResourceStack
{
public:
	Particle_PooledResourceStack() = default;
	Particle_PooledResourceStack(const Particle_PooledResourceStack&) = delete;
	Particle_PooledResourceStack& operator= (const Particle_PooledResourceStack&) = delete;
	~Particle_PooledResourceStack() = default;

	void Push(Particle_PooledResource*& resource);
	void Push(Particle_PooledResourceIterator& iterator);
	
	void Pop(Particle_PooledResourceIterator& iterator);

	/// <summary>Get the number of objects currently in the stack.</summary>
	/// <returns>const int reference to the size of the stack</returns> 
	const int& GetSize() const;

private:
	Particle_PooledResource* pFront = nullptr;
	int size = 0;
};
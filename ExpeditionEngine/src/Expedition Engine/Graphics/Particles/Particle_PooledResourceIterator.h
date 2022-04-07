#pragma once

#include "Particle_PooledResource.h"

//Used to interact with the Particle_PooledResource containers
class Particle_PooledResourceIterator
{
public:
	Particle_PooledResourceIterator() = default;
	Particle_PooledResourceIterator(const Particle_PooledResourceIterator& other);
	Particle_PooledResourceIterator& operator= (const Particle_PooledResourceIterator& other);
	~Particle_PooledResourceIterator() = default;

	/// <summary>Move along pNext</summary>
	Particle_PooledResourceIterator& operator++();

	/// <summary>Move along pPrevious</summary>
	Particle_PooledResourceIterator& operator--();

	/// <summary>Is this iterator on the final particle resource in the container?</summary>
	/// <returns>bool returns true if it is on the last particle resource</returns> 
	bool IsAtEnd() const;

	/// <summary>Is this iterator null?  This is useful for iterating over a container that may be empty.</summary>
	/// <returns>bool returns true if this iterator points to null</returns> 
	bool IsOutOfNodes() const;

	void SetResource(Particle_PooledResource& resource);
	void SetResource(Particle_PooledResource*& resource);

	Particle& GetCurrentParticle();
	Particle_PooledResource*& GetResource();

private:
	Particle_PooledResource* pResource;
};
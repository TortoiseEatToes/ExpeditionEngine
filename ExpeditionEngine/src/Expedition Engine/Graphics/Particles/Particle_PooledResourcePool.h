#pragma once

#include "Particle_PooledResourceStack.h"

#include "../../../Expedition Resources/GraphicsResourcesSettings.h"

//Stores an array of Particle_PooledResource objects
class Particle_PooledResourcePool
{
public:
	Particle_PooledResourcePool();
	Particle_PooledResourcePool(const Particle_PooledResourcePool&) = delete;
	Particle_PooledResourcePool& operator= (const Particle_PooledResourcePool&) = delete;
	~Particle_PooledResourcePool();

	void AcquireResource(Particle_PooledResourceIterator& iterator);
	void ReleaseResource(Particle_PooledResourceIterator& iterator);

	///<summary> Get the number of particle resources that are currently free to be used</summary>
	/// <returns>const reference to the int value of the number of free resources</returns> 
	const int& GetNumberOfAvailableResources() const;

private:
	Particle_PooledResourceStack unusedResourceStack;
	Particle_PooledResource resourcePool[NumberOfParticles];
};

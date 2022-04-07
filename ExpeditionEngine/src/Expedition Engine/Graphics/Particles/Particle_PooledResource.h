#pragma once
#include "Particle.h"

//Object that all Particle_PooledResource containers use
struct Particle_PooledResource
{
	Particle particle;
	Particle_PooledResource* pNext = nullptr;
	Particle_PooledResource* pPrevious = nullptr;
};
#pragma once

#include "ParticleEmitter.h"

class ParticleEmitterAttorney
{
public:
	struct ManagerControl
	{
	private:
		friend class ParticleEmitterManager;
		static void SpawnParticleBurstRepeating(ParticleEmitter* pParticleEmitter)
		{
			pParticleEmitter->SpawnParticleBurstRepeating();
		}

		static PriorityQueueArray<ParticleEmitter*, float>::Iterator& GetIterator(ParticleEmitter* pParticleEmitter)
		{
			return pParticleEmitter->GetIterator();
		}
	};

};
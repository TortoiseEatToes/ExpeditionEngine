#pragma once

#include "ParticleSettingsManager.h"
#include "../../Engine/ExpeditionEngine.h"

class ParticleSettingsManagerAttorney
{
public:
	struct LoadResourcesControl
	{
	private:
		//friend void ExpeditionEngine::LoadResources();
		friend class ExpeditionEngine;

		static void AllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, int maxNumberOfParticles)
		{
			ParticleSettingsManager::AllocateParticleMemory(particleName, pModel, pTexture, maxNumberOfParticles);
		}
	};
};
#include "ParticleSettingsManager.h"

#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"

void ParticleSettingsManager::AllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, int maxNumberOfParticles)
{
	GraphicsSceneManagerAttorney::ParticleSettingsManagerControl::AllocateParticleMemory(particleName, pModel, pTexture, maxNumberOfParticles);
}

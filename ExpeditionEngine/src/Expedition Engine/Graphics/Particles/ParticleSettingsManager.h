#pragma once

enum ParticleName;
class Model;
class Texture;

//Used during the engine start up to create all of the memory that the particle system will need
class ParticleSettingsManager
{
public:
	//Nothing

private:
	friend class ParticleSettingsManagerAttorney;

	static void AllocateParticleMemory(const ParticleName& particleName, Model* pModel, Texture* pTexture, int maxNumberOfParticles);

	//Nobody should actually create this guy for now, but we may want him to be a true singleton later
	ParticleSettingsManager() = delete;
	ParticleSettingsManager(const ParticleSettingsManager&) = delete;
	ParticleSettingsManager(ParticleSettingsManager&&) = delete;
	ParticleSettingsManager& operator=(const ParticleSettingsManager&) = delete;
	ParticleSettingsManager& operator=(ParticleSettingsManager&&) = delete;
	~ParticleSettingsManager() = delete;
};
#pragma once
#include "../../Containers/PriorityQueueArray.h"

#include "../../../Expedition Resources/SceneSettings.h"
#include "../../Graphics/Particles/ParticleBurstData.h"

#include "../SceneComponent.h"

//Used to spawn bursts of particles
class ParticleEmitter : public SceneComponent
{
public:
	ParticleEmitter() = delete;
	/// <summary>Create a particle emitter.  The scene to spawn particles in and the type of particles to spawn are both required.</summary>
	/// <param name="scene">The scene to spawn particles into</param>
	/// <param name="initParticleName">The name of the particle type to spawn</param>
	ParticleEmitter(const SceneName& scene, const ParticleName& initParticleName);
	ParticleEmitter(const ParticleEmitter&) = delete;
	ParticleEmitter(ParticleEmitter&&) = delete;
	ParticleEmitter& operator=(const ParticleEmitter&) = delete;
	ParticleEmitter& operator=(ParticleEmitter&&) = delete;
	virtual ~ParticleEmitter() override = default;

	/// <summary>Sends a request to spawn a particle burst with the current settings.</summary>
	void SpawnParticleBurst();

	/// <summary>Sends a request to spawn a particle burst with the current settings and a specific number of particles.</summary>
	/// <param name="numberOfParticles">The number of particles to spawn with this burst and future bursts</param>
	void SpawnParticleBurst(const int& numberOfParticles);

	/// <summary>Start spawning bursts after a fixed number of times.</summary>
	/// <param name="numberOfParticles">Number of particles to spawn with each burst</param>
	/// <param name="timeUntilConsecutiveBurst">Time between bursts of particles</param>
	void StartSpawnParticleBurstRepeating(const int& numberOfParticles, const float& timeUntilConsecutiveBurst);
	
	/// <summary>Sends a request to spawn a particle burst with the current settings.</summary>
	void StopSpawnParticleBurstRepeating();

	/// <summary>Change the type of particle to spawn bursts of.</summary>
	/// <param name="particleToUse">The name of the particle type to spawn bursts of</param>
	void ChangeParticle(const ParticleName& particleToUse);

	/// <summary>Set the starting position of particles spawned by this emitter without any randomness.</summary>
	void SetParticlePosition(const Vector4F& position);

	/// <summary>Set the starting position of particles spawned by this emitter.</summary>
	/// <param name="positionXMin">The lowest possible X value of the particle's starting position</param>
	/// <param name="positionXMax">The highest possible X value of the particle's starting position</param>
	/// <param name="positionYMin">The lowest possible Y value of the particle's starting position</param>
	/// <param name="positionYMax">The highest possible Y value of the particle's starting position</param>
	/// <param name="positionYMin">The lowest possible Z value of the particle's starting position</param>
	/// <param name="positionYMax">The highest possible Z value of the particle's starting position</param>
	void SetParticlePosition(const float& positionXMin, const float& positionXMax, 
							 const float& positionYMin, const float& positionYMax,
							 const float& positionZMin, const float& positionZMax);

	/// <summary>Set the starting velocity of particles spawned by this emitter without any randomness.</summary>
	void SetParticleVelocity(const Vector4F& velocity);

	/// <summary>Set the starting velocity of particles spawned by this emitter with some defined randomness.</summary>
	void SetParticleVelocity(const Vector4F& velocity, const float& randomnessOffset);

	/// <summary>Set the starting velocity of particles spawned by this emitter.</summary>
	/// <param name="velocityXMin">The lowest possible X value of the particle's starting velocity</param>
	/// <param name="velocityXMax">The highest possible X value of the particle's starting velocity</param>
	/// <param name="velocityYMin">The lowest possible Y value of the particle's starting velocity</param>
	/// <param name="velocityYMax">The highest possible Y value of the particle's starting velocity</param>
	/// <param name="velocityYMin">The lowest possible Z value of the particle's starting velocity</param>
	/// <param name="velocityYMax">The highest possible Z value of the particle's starting velocity</param>
	void SetParticleVelocity(const float& velocityXMin, const float& velocityXMax,
							 const float& velocityYMin, const float& velocityYMax,
							 const float& velocityZMin, const float& velocityZMax);

	/// <summary>Set the starting acceleration of particles spawned by this emitter without any randomness.</summary>
	void SetParticleAcceleration(const Vector4F& acceleration);

	/// <summary>Set the starting acceleration of particles spawned by this emitter.</summary>
	/// <param name="accelerationXMin">The lowest possible X value of the particle's starting acceleration</param>
	/// <param name="accelerationXMax">The highest possible X value of the particle's starting acceleration</param>
	/// <param name="accelerationYMin">The lowest possible Y value of the particle's starting acceleration</param>
	/// <param name="accelerationYMax">The highest possible Y value of the particle's starting acceleration</param>
	/// <param name="accelerationYMin">The lowest possible Z value of the particle's starting acceleration</param>
	/// <param name="accelerationYMax">The highest possible Z value of the particle's starting acceleration</param>
	void SetParticleAcceleration(const float& accelerationXMin, const float& accelerationXMax,
								 const float& accelerationYMin, const float& accelerationYMax,
								 const float& accelerationZMin, const float& accelerationZMax);

	/// <summary>Set the tint of the color of the particles that are spawned.</summary>
	/// <param name="colorR">The lowest possible Red value of the tint</param>
	/// <param name="colorR">The highest possible Red value of the tint</param>
	/// <param name="colorG">The lowest possible Green value of the tint</param>
	/// <param name="colorG">The highest possible Green value of the tint</param>
	/// <param name="colorB">The lowest possible Blue value of the tint</param>
	/// <param name="colorB">The highest possible Blue value of the tint</param>
	/// <param name="colorA">The lowest possible Alpha value of the tint</param>
	/// <param name="colorA">The highest possible Alpha value of the tint</param>
	void SetParticleColorTint(const float& colorTintRMin, const float& colorTintRMax, 
							  const float& colorTintGMin, const float& colorTintGMax,
							  const float& colorTintBMin, const float& colorTintBMax,
							  const float& colorTintAMin, const float& colorTintAMax);

	/// <summary>Set the tint of the color of the particles that are spawned.</summary>
	void SetParticleColorTint(const Vector4F& tint);

	/// <summary>Set the lifetime of particle bursts spawned by the emitter.</summary>
	/// <param name="baseValue">The base lifetime</param>
	/// <param name="minLifetime">The lowest possible lifetime value</param>
	/// <param name="maxLifetime">The highest possible lifetime value</param>
	void SetBurstLifetime(const float& minLifetime, const float& maxLifetime);

private:
	friend class ParticleEmitterAttorney;

	/// <summary>The user child implements this function to define what it means to register into a scene</summary>
	virtual void RegisterIntoSceneChild(EngineScene& engineScene) override;
	/// <summary>The user child implements this function to define what it means to deregister from a scene</summary>
	virtual void DeregisterFromSceneChild(EngineScene& engineScene) override;

	/// <summary>Private function called by the ParticleEmitterManager to repeatedly spawn bursts of particles.</summary>
	void SpawnParticleBurstRepeating();
	PriorityQueueArray<ParticleEmitter*, float>::Iterator& GetIterator() { return iterator; }

	ParticleBurstData particleBurstData;
	PriorityQueueArray<ParticleEmitter*, float>::Iterator iterator;
	float timeBetweenBursts = -1.0f;
	bool currentlyRegistered = false;
};
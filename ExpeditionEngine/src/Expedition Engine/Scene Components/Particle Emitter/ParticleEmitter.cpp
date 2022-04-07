#include "ParticleEmitter.h"

#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"
#include "../../Scenes/EngineScene.h"
#include "../../Math/MathTools.h"

#include <assert.h>

ParticleEmitter::ParticleEmitter(const SceneName& scene, const ParticleName& initParticleName)
{
	registeredScene = scene;
	particleBurstData.particleName = initParticleName;
	particleBurstData.textureName = GraphicsSceneManager::GetScene(scene)->GetParticleManager().GetParticleType(initParticleName).GetTextureName();
}

void ParticleEmitter::SpawnParticleBurst()
{
	GraphicsSceneManagerAttorney::ParticleEmitterControl::RequestParticleBurst(registeredScene, particleBurstData);
}

void ParticleEmitter::SpawnParticleBurst(const int& numberOfParticles)
{
	particleBurstData.numberOfParticles = numberOfParticles;
	SpawnParticleBurst();
}

void ParticleEmitter::StartSpawnParticleBurstRepeating(const int& numberOfParticles, const float& timeUntilConsecutiveBurst)
{
	//If you are currently registered, deregister
	if (currentlyRegistered)
	{
		DeregisterFromScene();
	}

	//Set your new values
	timeBetweenBursts = timeUntilConsecutiveBurst;
	particleBurstData.numberOfParticles = numberOfParticles;

	SpawnParticleBurst();

	//Register
	currentlyRegistered = true;
	RegisterIntoScene();
}

void ParticleEmitter::StopSpawnParticleBurstRepeating()
{
	if (currentlyRegistered)
	{
		currentlyRegistered = false;
		DeregisterFromScene();
	}
}

void ParticleEmitter::RegisterIntoSceneChild(EngineScene& engineScene)
{
	engineScene.GetParticleEmitterManager().RegisterParticleEmitterForBurst(this, timeBetweenBursts);
}

void ParticleEmitter::DeregisterFromSceneChild(EngineScene& engineScene)
{
	engineScene.GetParticleEmitterManager().DeregisterParticleEmitter(this);
}

void ParticleEmitter::SpawnParticleBurstRepeating()
{
	SpawnParticleBurst();
	RegisterIntoScene();
}

void ParticleEmitter::ChangeParticle(const ParticleName& particleToUse)
{
	particleBurstData.particleName = particleToUse;
}

void ParticleEmitter::SetParticlePosition(const Vector4F & position)
{
	particleBurstData.positionXMin = position.X();
	particleBurstData.positionXMax = position.X() + 0.00001f;

	particleBurstData.positionYMin = position.Y();
	particleBurstData.positionYMax = position.Y() + 0.00001f;

	particleBurstData.positionZMin = position.Z();
	particleBurstData.positionZMax = position.Z() + 0.00001f;
}

void ParticleEmitter::SetParticlePosition(const float & positionXMin, const float & positionXMax, const float & positionYMin, const float & positionYMax, const float & positionZMin, const float & positionZMax)
{
	assert(positionXMin <= positionXMax);
	assert(positionYMin <= positionYMax);
	assert(positionZMin <= positionZMax);

	particleBurstData.positionXMin = positionXMin;
	particleBurstData.positionXMax = positionXMax;

	particleBurstData.positionYMin = positionYMin;
	particleBurstData.positionYMax = positionYMax;

	particleBurstData.positionZMin = positionZMin;
	particleBurstData.positionZMax = positionZMax;
}

void ParticleEmitter::SetParticleVelocity(const Vector4F & velocity)
{
	particleBurstData.velocityXMin = velocity.X();
	particleBurstData.velocityXMax = velocity.X() + 0.00000000001f;

	particleBurstData.velocityYMin = velocity.Y();
	particleBurstData.velocityYMax = velocity.Y() + 0.00000000001f;

	particleBurstData.velocityZMin = velocity.Z();
	particleBurstData.velocityZMax = velocity.Z() + 0.00000000001f;
}

void ParticleEmitter::SetParticleVelocity(const Vector4F & velocity, const float& randomnessOffset)
{
	particleBurstData.velocityXMin = MathTools::RandomFloatIncludingNegatives(velocity.X() - randomnessOffset, velocity.X());
	particleBurstData.velocityXMax = MathTools::RandomFloatIncludingNegatives(velocity.X(), velocity.X() + randomnessOffset);

	particleBurstData.velocityYMin = MathTools::RandomFloatIncludingNegatives(velocity.Y() - randomnessOffset, velocity.Y());
	particleBurstData.velocityYMax = MathTools::RandomFloatIncludingNegatives(velocity.Y(), velocity.Y() + randomnessOffset);

	particleBurstData.velocityZMin = MathTools::RandomFloatIncludingNegatives(velocity.Z() - randomnessOffset, velocity.Z());
	particleBurstData.velocityZMax = MathTools::RandomFloatIncludingNegatives(velocity.Z(), velocity.Z() + randomnessOffset);
}

void ParticleEmitter::SetParticleVelocity(const float & velocityXMin, const float & velocityXMax, const float & velocityYMin, const float & velocityYMax, const float & velocityZMin, const float & velocityZMax)
{
	assert(velocityXMin <= velocityXMax);
	assert(velocityYMin <= velocityYMax);
	assert(velocityZMin <= velocityZMax);

	particleBurstData.velocityXMin = velocityXMin;
	particleBurstData.velocityXMax = velocityXMax;

	particleBurstData.velocityYMin = velocityYMin;
	particleBurstData.velocityYMax = velocityYMax;

	particleBurstData.velocityZMin = velocityZMin;
	particleBurstData.velocityZMax = velocityZMax;
}

void ParticleEmitter::SetParticleAcceleration(const Vector4F & acceleration)
{
	particleBurstData.accelerationXMin = acceleration.X();
	particleBurstData.accelerationXMax = acceleration.X() + 0.00000000001f;

	particleBurstData.accelerationYMin = acceleration.Y();
	particleBurstData.accelerationYMax = acceleration.Y() + 0.00000000001f;

	particleBurstData.accelerationZMin = acceleration.Z();
	particleBurstData.accelerationZMax = acceleration.Z() + 0.00000000001f;
}

void ParticleEmitter::SetParticleAcceleration(const float & accelerationXMin, const float & accelerationXMax, const float & accelerationYMin, const float & accelerationYMax, const float & accelerationZMin, const float & accelerationZMax)
{
	assert(accelerationXMin <= accelerationXMax);
	assert(accelerationYMin <= accelerationYMax);
	assert(accelerationZMin <= accelerationZMax);

	particleBurstData.accelerationXMin = accelerationXMin;
	particleBurstData.accelerationXMax = accelerationXMax;

	particleBurstData.accelerationYMin = accelerationYMin;
	particleBurstData.accelerationYMax = accelerationYMax;

	particleBurstData.accelerationZMin = accelerationZMin;
	particleBurstData.accelerationZMax = accelerationZMax;
}

void ParticleEmitter::SetParticleColorTint(const float & colorTintRMin, const float & colorTintRMax, const float & colorTintGMin, const float & colorTintGMax, const float & colorTintBMin, const float & colorTintBMax, const float & colorTintAMin, const float & colorTintAMax)
{
	assert(colorTintRMin <= colorTintRMax);
	assert(colorTintGMin <= colorTintGMax);
	assert(colorTintBMin <= colorTintBMax);
	assert(colorTintAMin <= colorTintAMax);

	particleBurstData.colorTintRMin = colorTintRMin;
	particleBurstData.colorTintRMax = colorTintRMax;

	particleBurstData.colorTintGMin = colorTintGMin;
	particleBurstData.colorTintGMax = colorTintGMax;

	particleBurstData.colorTintBMin = colorTintBMin;
	particleBurstData.colorTintBMax = colorTintBMax;

	particleBurstData.colorTintAMin = colorTintAMin;
	particleBurstData.colorTintAMax = colorTintAMax;
}

void ParticleEmitter::SetParticleColorTint(const Vector4F& tint)
{
	particleBurstData.colorTintRMin = tint.X();
	particleBurstData.colorTintRMax = tint.X() + 0.001f;

	particleBurstData.colorTintGMin = tint.Y();
	particleBurstData.colorTintGMax = tint.Y() + 0.001f;

	particleBurstData.colorTintBMin = tint.Z();
	particleBurstData.colorTintBMax = tint.Z() + 0.001f;

	particleBurstData.colorTintAMin = tint.W();
	particleBurstData.colorTintAMax = tint.W() + 0.001f;
}

void ParticleEmitter::SetBurstLifetime(const float & minLifetime, const float & maxLifetime)
{
	assert(minLifetime > 0.0f);
	assert(maxLifetime > minLifetime);

	particleBurstData.particleLifeMin = minLifetime;
	particleBurstData.particleLifeMax = maxLifetime;
}
#pragma once

#include "../../Containers/PriorityQueueArray.h"

class ParticleEmitter;
class SceneTimeManager;

//Used to store all of the repeating burst requests in one queue per scene
class ParticleEmitterManager
{
public:
	ParticleEmitterManager() = delete;
	ParticleEmitterManager(SceneTimeManager& pInitSceneTimeManager, const int& maxNumberOfBursts);
	ParticleEmitterManager(const ParticleEmitterManager&) = delete;
	ParticleEmitterManager(ParticleEmitterManager&&) = delete;
	ParticleEmitterManager& operator=(const ParticleEmitterManager&) = delete;
	ParticleEmitterManager& operator=(ParticleEmitterManager&&) = delete;
	~ParticleEmitterManager() = default;

	/// <summary>This function is called by the scene that owns this manager.  It is used to check if any alarms have timed out.</summary>
	/// <param name="currentTime">The current time of this scene</param>
	void ProcessParticleBursts(const float& currentTime);
	
	/// <summary>This function is called by the scene that owns this manager.  It is used to check if any alarms have timed out.</summary>
	/// <param name="pEmitter">The current time of this scene</param>
	/// <param name="timeUntilTrigger">The current time of this scene</param>
	void RegisterParticleEmitterForBurst(ParticleEmitter* pEmitter, const float& timeUntilTrigger);

	/// <summary>This function is called by the scene that owns this manager.  It is used to check if any alarms have timed out.</summary>
	/// <param name="pEmitter">The current time of this scene</param>
	void DeregisterParticleEmitter(ParticleEmitter* pEmitter);

private:
	PriorityQueueArray<ParticleEmitter*, float> burstQueue;
	SceneTimeManager* pSceneTimeManager;
	ParticleEmitter* pTempEmitter;
};
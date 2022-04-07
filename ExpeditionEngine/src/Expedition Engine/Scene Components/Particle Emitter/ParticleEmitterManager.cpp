#include "ParticleEmitterManager.h"
#include "ParticleEmitterAttorney.h"
#include "../../Time/SceneTimeManager.h"

ParticleEmitterManager::ParticleEmitterManager(SceneTimeManager& pInitSceneTimeManager, const int& maxNumberOfBursts)
	:burstQueue(maxNumberOfBursts)
{
	pSceneTimeManager = &pInitSceneTimeManager;
}

void ParticleEmitterManager::ProcessParticleBursts(const float& currentTime)
{
	while (burstQueue.Size() > 0 && currentTime > burstQueue.PeekFrontPriority())
	{
		burstQueue.Pop(pTempEmitter);
		ParticleEmitterAttorney::ManagerControl::SpawnParticleBurstRepeating(pTempEmitter);
	}
}

void ParticleEmitterManager::RegisterParticleEmitterForBurst(ParticleEmitter* pEmitter, const float& timeUntilTrigger)
{
	burstQueue.Push(pSceneTimeManager->GetCurrentSceneTime() + timeUntilTrigger, pEmitter, ParticleEmitterAttorney::ManagerControl::GetIterator(pEmitter));
}

void ParticleEmitterManager::DeregisterParticleEmitter(ParticleEmitter* pEmitter)
{
	burstQueue.Remove(ParticleEmitterAttorney::ManagerControl::GetIterator(pEmitter));
}

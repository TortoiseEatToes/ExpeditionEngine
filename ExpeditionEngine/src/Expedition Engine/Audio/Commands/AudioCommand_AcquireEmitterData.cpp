#include "AudioCommand_AcquireEmitterData.h"

#include "../EmitterData/AudioEmitterDataManager.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_AcquireEmitterData::Initialize(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pInitAudioEmitter, AudioEmitterCallback* pInitCallback, AudioClip& audioClip)
{
	pIterator = &outIterator;
	pCallback = pInitCallback;
	pAudioEmitter = pInitAudioEmitter;
	pAudioClip = &audioClip;
}

void AudioCommand_AcquireEmitterData::Execute(AudioSystem * const pAudioSystem)
{
	AudioSystemAttorney::AudioCommandControl::GetAudioEmitterDataManager(pAudioSystem).Acquire(*pIterator);
	pIterator->GetCurrentObject().Initialize(AudioSystemAttorney::AudioCommandControl::GetXAudio2(pAudioSystem), pAudioEmitter, pCallback, *pIterator, *pAudioClip);
}

void AudioCommand_AcquireEmitterData::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}

#include "AudioCommand_AcquireEmitterDataStreamed.h"

#include "../EmitterData/AudioEmitterDataManager.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_AcquireEmitterDataStreamed::Initialize(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pInitAudioEmitter, AudioEmitterCallback* pInitCallback, const char* audioFileName)
{
	pIterator = &outIterator;
	pCallback = pInitCallback;
	pAudioEmitter = pInitAudioEmitter;
	pAudioFileName = audioFileName;
}

void AudioCommand_AcquireEmitterDataStreamed::Execute(AudioSystem * const pAudioSystem)
{
	AudioSystemAttorney::AudioCommandControl::GetAudioEmitterDataManager(pAudioSystem).Acquire(*pIterator);
	pIterator->GetCurrentObject().Initialize(AudioSystemAttorney::AudioCommandControl::GetXAudio2(pAudioSystem), pAudioEmitter, pCallback, *pIterator, pAudioFileName);
}

void AudioCommand_AcquireEmitterDataStreamed::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}
#include "AudioCommand_Pause.h"

#include "../EmitterData/AudioEmitterData.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_Pause::Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData)
{
	pAudioEmitterData = &pInitAudioEmitterData;
}

void AudioCommand_Pause::Execute(AudioSystem * const pAudioSystem)
{
	pAudioEmitterData->GetCurrentObject().Pause();
}

void AudioCommand_Pause::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}
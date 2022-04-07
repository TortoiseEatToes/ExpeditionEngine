#include "AudioCommand_Stop.h"

#include "../EmitterData/AudioEmitterData.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_Stop::Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData)
{
	pAudioEmitterData = &pInitAudioEmitterData;
}

void AudioCommand_Stop::Execute(AudioSystem * const pAudioSystem)
{
	pAudioEmitterData->GetCurrentObject().Stop();
}

void AudioCommand_Stop::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}

#include "AudioCommand_SetVolume.h"

#include "../EmitterData/AudioEmitterData.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_SetVolume::Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const float & initVolume)
{
	pAudioEmitterData = &pInitAudioEmitterData;
	volume = initVolume;
}

void AudioCommand_SetVolume::Execute(AudioSystem * const pAudioSystem)
{
	pAudioEmitterData->GetCurrentObject().SetVolume(volume);
}

void AudioCommand_SetVolume::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}

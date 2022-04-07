#include "AudioCommand_SetVolumeMaster.h"

#include "../EmitterData/AudioEmitterData.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_SetVolumeMaster::Initialize(const float & initVolume)
{
	volume = initVolume;
}

void AudioCommand_SetVolumeMaster::Execute(AudioSystem * const pAudioSystem)
{
	AudioSystemAttorney::AudioCommandControl::cmdSetMasterVolume(pAudioSystem, volume);
}

void AudioCommand_SetVolumeMaster::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}
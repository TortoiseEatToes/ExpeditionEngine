#include "AudioCommand_SetPitch.h"

#include "../EmitterData/AudioEmitterData.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_SetPitch::Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const float & initTargetRatio)
{
	pAudioEmitterData = &pInitAudioEmitterData;
	targetRatio = initTargetRatio;
}

void AudioCommand_SetPitch::Execute(AudioSystem * const pAudioSystem)
{
	pAudioEmitterData->GetCurrentObject().SetPitch(targetRatio);
}

void AudioCommand_SetPitch::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}

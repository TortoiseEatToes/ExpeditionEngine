#include "AudioCommand_SetPan.h"

#include "../EmitterData/AudioEmitterData.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_SetPan::Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const float & initPanningValue)
{
	pAudioEmitterData = &pInitAudioEmitterData;
	panningValue = initPanningValue;
}

void AudioCommand_SetPan::Execute(AudioSystem * const pAudioSystem)
{
	pAudioEmitterData->GetCurrentObject().SetPan(AudioSystemAttorney::AudioCommandControl::GetMasteringVoice(pAudioSystem), panningValue);
}

void AudioCommand_SetPan::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}
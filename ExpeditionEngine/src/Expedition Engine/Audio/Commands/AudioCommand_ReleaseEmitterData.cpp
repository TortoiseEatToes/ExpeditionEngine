#include "AudioCommand_ReleaseEmitterData.h"

#include "../EmitterData/AudioEmitterDataManager.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_ReleaseEmitterData::Initialize(PooledResourceIterator<AudioEmitterData>& outIterator)
{
	pIterator = &outIterator;
}

void AudioCommand_ReleaseEmitterData::Execute(AudioSystem * const pAudioSystem)
{
	if (pIterator->GetCurrentObject().CheckIfInactive())
	{
		AudioSystemAttorney::AudioCommandControl::GetAudioEmitterDataManager(pAudioSystem).Release(*pIterator);
	}
}

void AudioCommand_ReleaseEmitterData::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}

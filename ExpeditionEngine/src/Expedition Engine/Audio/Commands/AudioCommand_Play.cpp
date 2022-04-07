#include "AudioCommand_Play.h"

#include "../EmitterData/AudioEmitterData.h"
#include "../AudioSystemAttorney.h"

void AudioCommand_Play::Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const unsigned int& initStartingPoint)
{
	pAudioEmitterData = &pInitAudioEmitterData;
	startingPoint = initStartingPoint;
}

void AudioCommand_Play::Execute(AudioSystem * const pAudioSystem)
{
	pAudioEmitterData->GetCurrentObject().Play(startingPoint);
}

void AudioCommand_Play::Recycle(AudioSystem * const audioSystem)
{
	AudioSystemAttorney::AudioCommandControl::RecycleAudioCommand(audioSystem, this);
}
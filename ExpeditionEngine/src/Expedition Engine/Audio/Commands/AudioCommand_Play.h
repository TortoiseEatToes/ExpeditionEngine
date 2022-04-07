#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_Play : public AudioCommand
{
public:
	AudioCommand_Play() = default;
	AudioCommand_Play(const AudioCommand_Play& other) = delete;
	AudioCommand_Play& operator= (const AudioCommand_Play& other) = delete;
	~AudioCommand_Play() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const unsigned int& initStartingPoint);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pAudioEmitterData;
	unsigned int startingPoint;
};
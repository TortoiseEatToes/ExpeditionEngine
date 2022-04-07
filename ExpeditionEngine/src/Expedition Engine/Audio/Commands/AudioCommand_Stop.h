#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_Stop : public AudioCommand
{
public:
	AudioCommand_Stop() = default;
	AudioCommand_Stop(const AudioCommand_Stop& other) = delete;
	AudioCommand_Stop& operator= (const AudioCommand_Stop& other) = delete;
	~AudioCommand_Stop() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pAudioEmitterData;
};
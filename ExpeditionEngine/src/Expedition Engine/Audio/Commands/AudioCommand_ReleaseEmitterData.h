#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_ReleaseEmitterData : public AudioCommand
{
public:
	AudioCommand_ReleaseEmitterData() = default;
	AudioCommand_ReleaseEmitterData(const AudioCommand_ReleaseEmitterData& other) = delete;
	AudioCommand_ReleaseEmitterData& operator= (const AudioCommand_ReleaseEmitterData& other) = delete;
	~AudioCommand_ReleaseEmitterData() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& outIterator);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pIterator;
};
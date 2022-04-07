#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_SetVolume : public AudioCommand
{
public:
	AudioCommand_SetVolume() = default;
	AudioCommand_SetVolume(const AudioCommand_SetVolume& other) = delete;
	AudioCommand_SetVolume& operator= (const AudioCommand_SetVolume& other) = delete;
	~AudioCommand_SetVolume() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const float& initVolume);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pAudioEmitterData;
	float volume;
};
#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_Pause : public AudioCommand
{
public:
	AudioCommand_Pause() = default;
	AudioCommand_Pause(const AudioCommand_Pause& other) = delete;
	AudioCommand_Pause& operator= (const AudioCommand_Pause& other) = delete;
	~AudioCommand_Pause() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pAudioEmitterData;
};
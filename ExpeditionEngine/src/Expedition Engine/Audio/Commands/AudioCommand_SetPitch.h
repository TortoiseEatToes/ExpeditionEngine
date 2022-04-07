#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_SetPitch : public AudioCommand
{
public:
	AudioCommand_SetPitch() = default;
	AudioCommand_SetPitch(const AudioCommand_SetPitch& other) = delete;
	AudioCommand_SetPitch& operator= (const AudioCommand_SetPitch& other) = delete;
	~AudioCommand_SetPitch() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const float& initTargetRatio);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pAudioEmitterData;
	float targetRatio;
};
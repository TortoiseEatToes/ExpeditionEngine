#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioEmitterCallback;
class AudioEmitter;
class AudioClip;

class AudioCommand_AcquireEmitterData : public AudioCommand
{
public:
	AudioCommand_AcquireEmitterData() = default;
	AudioCommand_AcquireEmitterData(const AudioCommand_AcquireEmitterData& other) = delete;
	AudioCommand_AcquireEmitterData& operator= (const AudioCommand_AcquireEmitterData& other) = delete;
	~AudioCommand_AcquireEmitterData() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pInitAudioEmitter, AudioEmitterCallback* pInitCallback, AudioClip& audioClip);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pIterator;
	AudioEmitterCallback* pCallback;
	AudioEmitter* pAudioEmitter;
	AudioClip* pAudioClip;
};
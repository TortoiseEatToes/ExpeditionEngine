#pragma once
#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioEmitterCallback;
class AudioEmitter;
class AudioClip;

class AudioCommand_AcquireEmitterDataStreamed : public AudioCommand
{
public:
	AudioCommand_AcquireEmitterDataStreamed() = default;
	AudioCommand_AcquireEmitterDataStreamed(const AudioCommand_AcquireEmitterDataStreamed& other) = delete;
	AudioCommand_AcquireEmitterDataStreamed& operator= (const AudioCommand_AcquireEmitterDataStreamed& other) = delete;
	~AudioCommand_AcquireEmitterDataStreamed() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pInitAudioEmitter, AudioEmitterCallback* pInitCallback, const char* audioFileName);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pIterator;
	AudioEmitterCallback* pCallback;
	AudioEmitter* pAudioEmitter;
	const char* pAudioFileName;
};
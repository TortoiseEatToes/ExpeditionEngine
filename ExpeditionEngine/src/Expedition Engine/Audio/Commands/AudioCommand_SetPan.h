#pragma once

#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_SetPan : public AudioCommand
{
public:
	AudioCommand_SetPan() = default;
	AudioCommand_SetPan(const AudioCommand_SetPan& other) = delete;
	AudioCommand_SetPan& operator= (const AudioCommand_SetPan& other) = delete;
	~AudioCommand_SetPan() = default;

	void Initialize(PooledResourceIterator<AudioEmitterData>& pInitAudioEmitterData, const float& initPanningValue);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const audioSystem) override;

private:
	PooledResourceIterator<AudioEmitterData>* pAudioEmitterData;
	float panningValue;
};
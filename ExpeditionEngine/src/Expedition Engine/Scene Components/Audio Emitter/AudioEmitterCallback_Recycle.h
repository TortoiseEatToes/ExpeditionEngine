#pragma once

#include "AudioEmitterCallback.h"

class AudioEmitterCallback_Recycle : public AudioEmitterCallback
{
public:
	AudioEmitterCallback_Recycle() = default;
	AudioEmitterCallback_Recycle(const AudioEmitterCallback_Recycle& other) = delete;
	AudioEmitterCallback_Recycle& operator= (const AudioEmitterCallback_Recycle& other) = delete;
	virtual ~AudioEmitterCallback_Recycle() = default;

protected:

	void OnAudioBegin(AudioEmitter& audioEmitter) override;
	void OnAudioEnd(AudioEmitter& audioEmitter) override;
	void OnAudioLoopEnd(AudioEmitter& audioEmitter)override;
	void OnAudioError(AudioEmitter& audioEmitter) override;
};
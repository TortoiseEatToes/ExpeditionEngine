#pragma once

#include "AudioEmitterCallback.h"

class AudioEmitterCallback_Null : public AudioEmitterCallback
{
public:
	AudioEmitterCallback_Null() = default;
	AudioEmitterCallback_Null(const AudioEmitterCallback_Null& other) = delete;
	AudioEmitterCallback_Null& operator= (const AudioEmitterCallback_Null& other) = delete;
	virtual ~AudioEmitterCallback_Null() = default;

	static AudioEmitterCallback_Null& Instance()
	{
		static AudioEmitterCallback_Null nullCallback;
		return nullCallback;
	}

protected:

	void OnAudioBegin(AudioEmitter* const audioEmitter) override;
	void OnAudioEnd(AudioEmitter* const audioEmitter) override;
	void OnAudioLoopEnd(AudioEmitter* const audioEmitter)override;
	void OnAudioError(AudioEmitter* const audioEmitter) override;
};
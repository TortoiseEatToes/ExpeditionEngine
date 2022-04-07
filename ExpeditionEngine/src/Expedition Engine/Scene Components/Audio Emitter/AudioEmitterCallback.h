#pragma once

class AudioEmitter;

class AudioEmitterCallback
{
public:
	AudioEmitterCallback() = default;
	AudioEmitterCallback(const AudioEmitterCallback& other) = delete;
	AudioEmitterCallback& operator= (const AudioEmitterCallback& other) = delete;
	virtual ~AudioEmitterCallback() = default;

	virtual void OnAudioBegin(AudioEmitter* const audioEmitter){};
	virtual void OnAudioEnd(AudioEmitter* const audioEmitter){};
	virtual void OnAudioLoopEnd(AudioEmitter* const audioEmitter){};
	virtual void OnAudioError(AudioEmitter* const audioEmitter){};

private:
	friend class AudioEmitterCallbackAttorney;
};
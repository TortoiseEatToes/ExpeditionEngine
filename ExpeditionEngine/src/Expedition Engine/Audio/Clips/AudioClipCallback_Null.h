#pragma once

#include "AudioClipCallback.h"

class AudioClipCallback_Null : public AudioClipCallback
{
public:
	AudioClipCallback_Null() = default;
	AudioClipCallback_Null(const AudioClipCallback_Null& other) = delete;
	AudioClipCallback_Null& operator= (const AudioClipCallback_Null& other) = delete;
	virtual ~AudioClipCallback_Null() = default;

	static AudioClipCallback_Null& Instance()
	{
		static AudioClipCallback_Null audioClipCallback_Null;
		return audioClipCallback_Null;
	}

	void OnBufferLoadSuccess() override;
	void OnBufferLoadFail() override;
};
#pragma once

class AudioClipCallback
{
public:
	AudioClipCallback() = default;
	AudioClipCallback(const AudioClipCallback& other) = delete;
	AudioClipCallback& operator= (const AudioClipCallback& other) = delete;
	virtual ~AudioClipCallback() = default;

	virtual void OnBufferLoadSuccess() = 0;
	virtual void OnBufferLoadFail() = 0;
};
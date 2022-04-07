#pragma once

#include "../../Containers/PooledResourceIterator.h"
#include "../EmitterData/AudioEmitterBuffer_Streamed.h"

#include <Xaudio2.h>
#include <mutex>

class AudioClip;
class AudioEmitter;
class AudioEmitterCallback;

//This data is protected because only the AudioSystem can interact with it using the commands
class AudioEmitterData : public IXAudio2VoiceCallback
{
public:
	AudioEmitterData();
	AudioEmitterData(const AudioEmitterData& other) = delete;
	AudioEmitterData& operator= (const AudioEmitterData& other) = delete;
	~AudioEmitterData();

	//State controls
	void Initialize(IXAudio2* pXAudio2, AudioEmitter* pInitAudioEmitter, AudioEmitterCallback* pInitCallback, PooledResourceIterator<AudioEmitterData>& initIterator, AudioClip& audioClip);
	void Initialize(IXAudio2* pXAudio2, AudioEmitter* pInitAudioEmitter, AudioEmitterCallback* pInitCallback, PooledResourceIterator<AudioEmitterData>& initIterator, const char* audioFileName);
	bool CheckIfInactive();
	void Sanitize();

	//Source voice controls
	void Play(const unsigned int& startingPoint);
	void Pause();
	void Stop();

	void SetVolume(const float& volume);
	void SetPitch(const float & targetRatio);
	void SetPan(IXAudio2MasteringVoice* pMasterVoice, const float& panningValue);

private:
	enum State
	{
		Pooled,
		Inactive,
		Active,
		MarkedForRecycling
	};

	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 v) override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override;
	void STDMETHODCALLTYPE OnBufferStart(void * pointerVoid) override;
	void STDMETHODCALLTYPE OnBufferEnd(void * pointerVoid) override;
	void STDMETHODCALLTYPE OnStreamEnd() override;
	void STDMETHODCALLTYPE OnLoopEnd(void * pointerVoid) override;
	void STDMETHODCALLTYPE OnVoiceError(void * pointerVoid, HRESULT result) override;

	void LoadAudioClipIntoSourceVoice();

	XAUDIO2_BUFFER buffer = { 0 };
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	std::mutex mutex;
	AudioEmitter* pAudioEmitter;
	AudioEmitterCallback* pEmitterCallback;
	AudioEmitterBuffer_Streamed streamedAudioBuffer;
	std::string defaultPath = "Assets/Audio/";
	PooledResourceIterator<AudioEmitterData> iterator;
	AudioClip* pCurrentAudioClip = nullptr;
	const char* pStreamedAudioFileName = nullptr;
	State currentState = State::Pooled;
	bool isStreaming = false;
};
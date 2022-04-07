#include "AudioEmitterData.h"

#include "x3daudio.h"

#include "../AudioSystemAttorney.h"
#include "../../Scene Components/Audio Emitter/AudioEmitterCallback.h"

#include "../Clips/AudioClip.h"

#include <assert.h>


AudioEmitterData::AudioEmitterData()
{
}

AudioEmitterData::~AudioEmitterData()
{
}

void AudioEmitterData::Initialize(IXAudio2* pXAudio2, AudioEmitter* pInitAudioEmitter, AudioEmitterCallback* pInitCallback, PooledResourceIterator<AudioEmitterData>& initIterator, AudioClip& audioClip)
{
	pAudioEmitter = pInitAudioEmitter;
	pEmitterCallback = pInitCallback;
	iterator = initIterator;

	WAVEFORMATEXTENSIBLE* pTempFormat;
	audioClip.GetWaveFormat(pTempFormat);
	HRESULT hResult = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)pTempFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, this);
	assert(!FAILED(hResult));

	pCurrentAudioClip = &audioClip;
	LoadAudioClipIntoSourceVoice();
	currentState = State::Inactive;
}

void AudioEmitterData::Initialize(IXAudio2 * pXAudio2, AudioEmitter * pInitAudioEmitter, AudioEmitterCallback * pInitCallback, PooledResourceIterator<AudioEmitterData>& initIterator, const char * audioFileName)
{
	pAudioEmitter = pInitAudioEmitter;
	pEmitterCallback = pInitCallback;
	iterator = initIterator;

	pStreamedAudioFileName = audioFileName;
	streamedAudioBuffer.LoadFormat(defaultPath + audioFileName);

	HRESULT hResult = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)streamedAudioBuffer.GetWaveFormat(), 0, XAUDIO2_DEFAULT_FREQ_RATIO, this);
	assert(!FAILED(hResult));

	streamedAudioBuffer.SetSourceVoice(pSourceVoice);

	streamedAudioBuffer.BeginStreaming();
	isStreaming = true;

	currentState = State::Inactive;
}

bool AudioEmitterData::CheckIfInactive()
{
	bool flag = true;

	mutex.lock();
	assert(currentState != State::Pooled);

	if (currentState == State::Active)
	{
		currentState = State::MarkedForRecycling;
		flag = false;
	}
	mutex.unlock();

	return flag;
}

void AudioEmitterData::OnVoiceProcessingPassStart(UINT32 v)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	//assert(currentState != State::Inactive);

	mutex.unlock();
}

void AudioEmitterData::OnVoiceProcessingPassEnd()
{
	mutex.lock();

	assert(currentState != State::Pooled);
	//assert(currentState != State::Inactive);

	mutex.unlock();
}

void AudioEmitterData::OnBufferStart(void * pointerVoid)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	//assert(currentState != State::Inactive);

	if (currentState != State::MarkedForRecycling)
	{
		pEmitterCallback->OnAudioBegin(pAudioEmitter);
	}

	mutex.unlock();
}

void AudioEmitterData::OnBufferEnd(void * pointerVoid)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	//assert(currentState != State::Inactive);

	if (isStreaming)
	{
		if (!streamedAudioBuffer.BufferComplete())
		{
			isStreaming = false;
		}
	}

	mutex.unlock();
}

void AudioEmitterData::OnStreamEnd()
{
	mutex.lock();

	assert(currentState != State::Pooled);
	assert(currentState != State::Inactive);

	if (currentState != State::MarkedForRecycling)
	{
		//Reset the audio data
		if (pCurrentAudioClip != nullptr)
		{
			LoadAudioClipIntoSourceVoice();
		}
		else
		{
			assert(pStreamedAudioFileName == nullptr);
			streamedAudioBuffer.LoadFormat(defaultPath + pStreamedAudioFileName);
			streamedAudioBuffer.BeginStreaming();
		}
		pEmitterCallback->OnAudioEnd(pAudioEmitter);
	}
	else
	{
		AudioSystemAttorney::AudioEmitterDataControl::ReleaseAudioEmitterData(iterator);
	}

	mutex.unlock();
}

void AudioEmitterData::OnLoopEnd(void * pointerVoid)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	assert(currentState != State::Inactive);

	if (currentState != State::MarkedForRecycling)
	{
		pEmitterCallback->OnAudioLoopEnd(pAudioEmitter);
	}

	mutex.unlock();
}

void AudioEmitterData::OnVoiceError(void * pointerVoid, HRESULT result)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	assert(currentState != State::Inactive);

	if (currentState != State::MarkedForRecycling)
	{
		pEmitterCallback->OnAudioError(pAudioEmitter);
	}

	mutex.unlock();
}

void AudioEmitterData::LoadAudioClipIntoSourceVoice()
{
	pCurrentAudioClip->LoadDataIntoBuffer(buffer);
	pSourceVoice->SubmitSourceBuffer(&buffer);
}

void AudioEmitterData::Sanitize()
{
	currentState = State::Pooled;

	pSourceVoice->DestroyVoice();
	pSourceVoice = nullptr;

	pCurrentAudioClip = nullptr;
	pStreamedAudioFileName = nullptr;
}

void AudioEmitterData::Play(const unsigned int& startingPoint)
{
	mutex.lock();

	assert(currentState == State::Inactive);


	//TODO: talk to sara
	pSourceVoice->SubmitSourceBuffer(&buffer);

	HRESULT hResult = pSourceVoice->Start(startingPoint);
	assert(!FAILED(hResult));
	currentState = State::Active;

	mutex.unlock();
}

void AudioEmitterData::Pause()
{
	mutex.lock();

	assert(currentState == State::Active);

	HRESULT hResult = pSourceVoice->Stop();
	assert(!FAILED(hResult));
	currentState = State::Inactive;

	mutex.unlock();
}

void AudioEmitterData::Stop()
{
	mutex.lock();

	streamedAudioBuffer.ForceStop();

	assert(currentState == State::Active);

	HRESULT hResult = pSourceVoice->Stop(0);
	assert(!FAILED(hResult));

	hResult = pSourceVoice->FlushSourceBuffers();
	assert(!FAILED(hResult));

	currentState = State::Inactive;

	mutex.unlock();
}

void AudioEmitterData::SetVolume(const float & volume)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	assert(currentState != State::MarkedForRecycling);

	pSourceVoice->SetVolume(volume);

	mutex.unlock();
}

void AudioEmitterData::SetPitch(const float & targetRatio)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	assert(currentState != State::MarkedForRecycling);

	pSourceVoice->SetFrequencyRatio(targetRatio);

	mutex.unlock();
}

void AudioEmitterData::SetPan(IXAudio2MasteringVoice * pMasterVoice, const float & panningValue)
{
	mutex.lock();

	assert(currentState != State::Pooled);
	assert(currentState != State::MarkedForRecycling);

	//Get the current channel mask values
	DWORD dwChannelMask;
	pMasterVoice->GetChannelMask(&dwChannelMask);

	//Create the output array
	float outputMatrix[8];
	for (int i = 0; i < 8; i++)
	{
		outputMatrix[i] = 0.0f;
	}

	// pan of -1.0 indicates all left speaker, 
	// 1.0 is all right speaker, 0.0 is split between left and right
	float left = 0.5f - panningValue / 2.0f;
	float right = 0.5f + panningValue / 2.0f;

	//Set up the values for all sound types (not important for us right now)
	switch (dwChannelMask)
	{
	case SPEAKER_MONO:
		outputMatrix[0] = 1.0;
		break;
	case SPEAKER_STEREO:
	case SPEAKER_2POINT1:
	case SPEAKER_SURROUND:
		outputMatrix[0] = left;
		outputMatrix[1] = right;
		break;
	case SPEAKER_QUAD:
		outputMatrix[0] = outputMatrix[2] = left;
		outputMatrix[1] = outputMatrix[3] = right;
		break;
	case SPEAKER_4POINT1:
		outputMatrix[0] = outputMatrix[3] = left;
		outputMatrix[1] = outputMatrix[4] = right;
		break;
	case SPEAKER_5POINT1:
	case SPEAKER_7POINT1:
	case SPEAKER_5POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = left;
		outputMatrix[1] = outputMatrix[5] = right;
		break;
	case SPEAKER_7POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = outputMatrix[6] = left;
		outputMatrix[1] = outputMatrix[5] = outputMatrix[7] = right;
		break;
	}

	//Push the new values to the master and source sounds
	XAUDIO2_VOICE_DETAILS VoiceDetails;
	pSourceVoice->GetVoiceDetails(&VoiceDetails);

	XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
	pMasterVoice->GetVoiceDetails(&MasterVoiceDetails);

	pSourceVoice->SetOutputMatrix(NULL, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix);

	mutex.unlock();
}

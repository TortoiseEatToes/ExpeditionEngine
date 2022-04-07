#include "AudioEmitter.h"

#include "../../Audio/AudioSystemAttorney.h"

#include "../../Audio/Clips/AudioClipManagerAttorney.h"

#include <assert.h>


AudioEmitter::AudioEmitter(const AudioClipName& audioClipName)
{
	AudioSystemAttorney::AudioEmitterControl::AcquireAudioEmitterData(iteratorData, this, &AudioEmitterCallback_Null::Instance(), AudioClipManagerAttorney::AudioEmitterControl::GetAudioClip(audioClipName));
	InitializeEmitter();
}

AudioEmitter::AudioEmitter(const AudioClipName& audioClipName, AudioEmitterCallback * pCallback)
{
	AudioSystemAttorney::AudioEmitterControl::AcquireAudioEmitterData(iteratorData, this, pCallback, AudioClipManagerAttorney::AudioEmitterControl::GetAudioClip(audioClipName));
	InitializeEmitter();
}

AudioEmitter::AudioEmitter(const char * audioFileName)
{
	AudioSystemAttorney::AudioEmitterControl::AcquireAudioEmitterData(iteratorData, this, &AudioEmitterCallback_Null::Instance(), audioFileName);
	isStreaming = true;
	InitializeEmitter();
}

AudioEmitter::AudioEmitter(const char * audioFileName, AudioEmitterCallback * pCallback)
{
	AudioSystemAttorney::AudioEmitterControl::AcquireAudioEmitterData(iteratorData, this, pCallback, audioFileName);
	isStreaming = true;
	InitializeEmitter();
}

AudioEmitter::~AudioEmitter()
{
	AudioSystemAttorney::AudioEmitterControl::ReleaseAudioEmitterData(iteratorData);
}

AudioEmitter::Result AudioEmitter::Play(const int& priority, const unsigned int& startingPoint)
{
	Result result = Result::SUCCESS;

	mutex.lock();
	if (currentStatus != Status::PLAYING)
	{
		if (AudioSystemAttorney::AudioEmitterControl::TryPlay(this, priority, startingPoint))
		{
			priorityLevel = priority;
			currentStatus = Status::PLAYING;
		}
		else
		{
			result = Result::FAILURE_PRIORITY_TOO_LOW;
		}
	}
	mutex.unlock();

	return result;
}

AudioEmitter::Result AudioEmitter::Pause()
{
	Result result = Result::SUCCESS;

	mutex.lock();
	if (currentStatus == Status::PLAYING)
	{
		AudioSystemAttorney::AudioEmitterControl::Pause(this);
		currentStatus = Status::PAUSED;
	}
	mutex.unlock();

	return result;
}

AudioEmitter::Result AudioEmitter::Stop()
{
	Result result = Result::SUCCESS;

	mutex.lock();
	if (currentStatus == Status::PLAYING)
	{
		AudioSystemAttorney::AudioEmitterControl::Stop(this);
		currentStatus = Status::STOPPED;
	}
	mutex.unlock();

	return result;
}

void AudioEmitter::Start3DUpdating()
{
	if (!isUpdating3DPosition)
	{
		RegisterIntoScene();
	}
}

void AudioEmitter::Stop3DUpdating()
{
	if (isUpdating3DPosition)
	{
		DeregisterFromScene();
	}
}

void AudioEmitter::SetPosition(const Vector4F & initPosition)
{
}

void AudioEmitter::SetVelocity(const Vector4F & initVelocity)
{
}

void AudioEmitter::SetOrientFront(const Vector4F & initOrientFront)
{
}

void AudioEmitter::SetOrientTop(const Vector4F & initOrientTop)
{
}

void AudioEmitter::SetVolume(const float & volume)
{
	AudioSystemAttorney::AudioEmitterControl::SetVolume(iteratorData, volume);
	currentVolume = volume;
}

float AudioEmitter::GetVolume() const
{
	return currentVolume;
}

void AudioEmitter::SetPitch(const float & targetRatio)
{
	AudioSystemAttorney::AudioEmitterControl::SetPitch(iteratorData, targetRatio);
	currentPitch = targetRatio;
}

float AudioEmitter::GetPitch() const
{
	return currentPitch;
}

void AudioEmitter::SetPan(const float & panningValue)
{
	AudioSystemAttorney::AudioEmitterControl::SetPan(iteratorData, panningValue);
	currentPan = panningValue;
}

float AudioEmitter::GetPan() const
{
	return currentPan;
}

AudioEmitter::Status AudioEmitter::GetCurrentStatus()
{
	return currentStatus;
}

void AudioEmitter::InitializeEmitter()
{
	emitter.ChannelCount = 1;
	emitter.CurveDistanceScaler = FLT_MIN;
}

void AudioEmitter::RegisterIntoSceneChild(EngineScene& engineScene)
{
}

void AudioEmitter::DeregisterFromSceneChild(EngineScene& engineScene)
{
}

PooledResourceIterator<AudioEmitterData>& AudioEmitter::GetAudioEmitterData()
{
	return iteratorData;
}

PriorityQueueArray<AudioEmitter*, int>::Iterator & AudioEmitter::GetPriorityTableIterator()
{
	return iteratorPriority;
}

void AudioEmitter::StopForcedByAudioSystem()
{
	mutex.lock();

	currentStatus = Status::STOPPED;
	AudioSystemAttorney::AudioEmitterControl::StopForcedByAudioSystem(this);

	mutex.unlock();
}

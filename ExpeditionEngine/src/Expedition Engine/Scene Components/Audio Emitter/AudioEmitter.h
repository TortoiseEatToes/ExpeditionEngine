#pragma once

#include "../SceneComponent.h"

#include "../../Containers/PooledResourceIterator.h"
#include "AudioEmitterCallback_Null.h"
#include "../../../Expedition Resources/AudioSettings.h"

#include "../../Containers/PriorityQueueArray.h"
#include "../../Math/Vector/Vector4F.h"

#include <mutex>

#include <windows.h>
#include <x3daudio.h>

class AudioEmitterData;
class AudioEmitterCallback;


class AudioEmitter : public SceneComponent
{
public:
	enum Status
	{
		PLAYING,
		PAUSED,
		STOPPED
	};

	enum Result
	{
		FAILURE_PRIORITY_TOO_LOW = -2,
		FAILURE = -1,
		SUCCESS
	};

	AudioEmitter() = delete;
	AudioEmitter(const AudioClipName& audioClipName);
	AudioEmitter(const AudioClipName& audioClipName, AudioEmitterCallback* pCallback);
	AudioEmitter(const char* audioFileName);
	AudioEmitter(const char* audioFileName, AudioEmitterCallback* pCallback);
	AudioEmitter(const AudioEmitter& other) = delete;
	AudioEmitter& operator= (const AudioEmitter& other) = delete;
	~AudioEmitter();

	/// <summary>Play.</summary>
	AudioEmitter::Result Play(const int& priority, const unsigned int& startingPoint = 0u);
	/// <summary>Pause.</summary>
	AudioEmitter::Result Pause();
	/// <summary>Stop.</summary>
	AudioEmitter::Result Stop();

	void Start3DUpdating();
	void Stop3DUpdating();

	void SetPosition(const Vector4F& initPosition);
	void SetVelocity(const Vector4F& initVelocity);
	void SetOrientFront(const Vector4F& initOrientFront);
	void SetOrientTop(const Vector4F& initOrientTop);
	

	void SetVolume(const float& volume);
	float GetVolume() const;

	void SetPitch(const float & targetRatio);
	float GetPitch() const;

	void SetPan(const float& panningValue);
	float GetPan() const;

	AudioEmitter::Status GetCurrentStatus();

private:
	friend class AudioEmitterAttorney;

	void InitializeEmitter();

	/// <summary>The user child implements this function to define what it means to register into a scene</summary>
	void RegisterIntoSceneChild(EngineScene& engineScene) override;
	/// <summary>The user child implements this function to define what it means to deregister from a scene</summary>
	void DeregisterFromSceneChild(EngineScene& engineScene) override;

	PooledResourceIterator<AudioEmitterData>& GetAudioEmitterData();
	PriorityQueueArray<AudioEmitter*, int>::Iterator& GetPriorityTableIterator();

	void StopForcedByAudioSystem();

	X3DAUDIO_EMITTER emitter;
	std::mutex mutex;
	PooledResourceIterator<AudioEmitterData> iteratorData;
	PriorityQueueArray<AudioEmitter*, int>::Iterator iteratorPriority;

	Status currentStatus = Status::STOPPED;
	float currentVolume = 0.7f;
	float currentPitch = 1.0f;
	float currentPan = 0.0f;
	int priorityLevel = 0;
	bool isStreaming = false;
	bool isUpdating3DPosition = false;
};
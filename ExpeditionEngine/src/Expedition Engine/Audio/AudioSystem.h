#pragma once

#include "EmitterData/AudioEmitterDataManager.h"

#include "../Engine/Tasks/Task_ProcessAudioCommands.h"
#include "AudioPriorityTable.h"

#include "../Containers/Pool.h"
#include "../Containers/Queue.h"

#include <x3daudio.h>
#include <mutex>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class AudioCommand;

class AudioCommand_Pause;
class AudioCommand_Play;
class AudioCommand_Stop;

class AudioCommand_AcquireEmitterData;
class AudioCommand_AcquireEmitterDataStreamed;
class AudioCommand_ReleaseEmitterData;

class AudioCommand_SetPan;
class AudioCommand_SetPitch;
class AudioCommand_SetVolume;
class AudioCommand_SetVolumeMaster;

class AudioEmitterCallback;

class AudioSystem
{
public:
	static void SetMasterVolume(const float& newMasterVolume)
	{
		Instance()->privSetMasterVolume(newMasterVolume);
	}

	static float GetMasterVolume()
	{
		return Instance()->masterVolume;
	}

	static void StopAllSounds()
	{
		Instance()->privStopAllSounds();
	}

private:
	friend class AudioSystemAttorney;

	AudioSystem();
	AudioSystem(const AudioSystem& other) = delete;
	AudioSystem& operator= (const AudioSystem& other) = delete;
	~AudioSystem();

	static AudioSystem* pInstance;

	static AudioSystem* Instance()
	{
		return pInstance;
	}
	static void Initialize()
	{
		pInstance = new AudioSystem();
	}
	static void Terminate()
	{
		delete pInstance;
	}

	void privSetMasterVolume(const float& newMasterVolume);
	void privStopAllSounds();

	//-------------- Audio Emitter Calls ----------------------------------
	//These require mutex protections because they need to protect the pools and the command queue
	static void Pause(AudioEmitter * const pAudioEmitter){Instance()->privPause(pAudioEmitter);}
	void privPause(AudioEmitter * const pAudioEmitter);

	static bool Play(AudioEmitter * const pAudioEmitter, const unsigned int& priority, const unsigned int& startingPoint) { return Instance()->privPlay(pAudioEmitter, priority, startingPoint); }
	bool privPlay(AudioEmitter * const pAudioEmitter, const unsigned int& priority, const unsigned int& startingPoint);

	static void Stop(AudioEmitter * const pAudioEmitter){Instance()->privStop(pAudioEmitter);}
	void privStop(AudioEmitter * const pAudioEmitter);

	static void AcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pAudioEmitter, AudioEmitterCallback* pCallback, AudioClip& audioClip) 
	{Instance()->privAcquireAudioEmitterData(outIterator, pAudioEmitter, pCallback, audioClip); }
	void privAcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pAudioEmitter, AudioEmitterCallback* pCallback, AudioClip& audioClip);

	static void AcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pAudioEmitter, AudioEmitterCallback* pCallback, const char * audioFileName)
	{Instance()->privAcquireAudioEmitterData(outIterator, pAudioEmitter, pCallback, audioFileName);}
	void privAcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pAudioEmitter, AudioEmitterCallback* pCallback, const char * audioFileName);

	static void ReleaseAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator) { Instance()->privReleaseAudioEmitterData(outIterator); }
	void privReleaseAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator);

	static void SetVolume(PooledResourceIterator<AudioEmitterData>& outIterator, const float& volume){Instance()->privSetVolume(outIterator, volume);}
	void privSetVolume(PooledResourceIterator<AudioEmitterData>& outIterator, const float& volume);

	static void SetPitch(PooledResourceIterator<AudioEmitterData>& outIterator, const float & targetRatio){Instance()->privSetPitch(outIterator, targetRatio);}
	void privSetPitch(PooledResourceIterator<AudioEmitterData>& outIterator, const float & targetRatio);

	static void SetPan(PooledResourceIterator<AudioEmitterData>& outIterator, const float& panningValue){Instance()->privSetPan(outIterator, panningValue);}
	void privSetPan(PooledResourceIterator<AudioEmitterData>& outIterator, const float& panningValue);
	//------------------------------------------------------------------------

	//---------- Audio Emitter calls that are forced by the engine ----------------
	static void StopForcedByAudioSystem(AudioEmitter * const pAudioEmitter) { Instance()->privStopForcedByAudioSystem(pAudioEmitter); }
	void privStopForcedByAudioSystem(AudioEmitter * const pAudioEmitter);
	//---------------------------------------------------

	//----------------- Direct engine calls ----------------------
	static void FinalExecution() { Instance()->privFinalExecution(); }
	void privFinalExecution();
	//----------------------------------------------------------------------

	//-------------- Audio Command Calls ----------------------------------
	//NOTE!!!  These are internally thread safe because they are only called after the execute
	IXAudio2* GetXAudio2();
	IXAudio2MasteringVoice* GetMasteringVoice();
	AudioEmitterDataManager& GetAudioEmitterDataManager();

	void cmdSetMasterVolume(const float& newMasterVolume);

	void RecycleAudioCommand(AudioCommand_Pause* pAudioCommand_Pause);
	void RecycleAudioCommand(const AudioCommand_Play* pAudioCommand_Play);
	void RecycleAudioCommand(const AudioCommand_Stop* pAudioCommand_Stop);

	void RecycleAudioCommand(const AudioCommand_AcquireEmitterData* pAudioCommand_AcquireEmitterData);
	void RecycleAudioCommand(const AudioCommand_AcquireEmitterDataStreamed* pAudioCommand_AcquireEmitterDataStreamed);
	void RecycleAudioCommand(const AudioCommand_ReleaseEmitterData* pAudioCommand_ReleaseEmitterData);

	void RecycleAudioCommand(const AudioCommand_SetPan* pAudioCommand_SetPan);
	void RecycleAudioCommand(const AudioCommand_SetPitch* pAudioCommand_SetPitch);
	void RecycleAudioCommand(const AudioCommand_SetVolume* pAudioCommand_SetVolume);
	void RecycleAudioCommand(const AudioCommand_SetVolumeMaster* pAudioCommand_SetVolumeMaster);
	//---------------------------------------------------------------------

	//This is called by a worker thread anytime there are commands in the queue
	static void ProcessAudioCommands(){Instance()->privProcessAudioCommands();}
	void privProcessAudioCommands();

	void SubmitStopCommand(AudioEmitter * const pAudioEmitter);

	AudioEmitterDataManager audioEmitterDataManager;
	AudioPriorityTable priorityTable;

	Pool<AudioCommand_Pause> poolAudioCommand_Pause;
	Pool<AudioCommand_Play> poolAudioCommand_Play;
	Pool<AudioCommand_Stop> poolAudioCommand_Stop;
	Pool<AudioCommand_AcquireEmitterData> poolAudioCommand_AcquireEmitterData;
	Pool<AudioCommand_AcquireEmitterDataStreamed> poolAudioCommand_AcquireEmitterDataStreamed;
	Pool<AudioCommand_ReleaseEmitterData> poolAudioCommand_ReleaseEmitterData;
	Pool<AudioCommand_SetPan> poolAudioCommand_SetPan;
	Pool<AudioCommand_SetPitch> poolAudioCommand_SetPitch;
	Pool<AudioCommand_SetVolume> poolAudioCommand_SetVolume;
	Pool<AudioCommand_SetVolumeMaster> poolAudioCommand_SetVolumeMaster;
	Queue<AudioCommand*> commandQueue;
	AudioCommand* pCurrentCommand;

	X3DAUDIO_HANDLE X3DAudio;
	X3DAUDIO_DSP_SETTINGS DSPSettings;
	XAUDIO2_VOICE_DETAILS voiceDetails;
	std::mutex audioCommandQueueMutex;
	//std::mutex audioCallbacksQueueMutex;
	IXAudio2* pXAudio2 = nullptr;
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;
	FLOAT32 * matrixDSP;
	float masterVolume = 1.0f;
};
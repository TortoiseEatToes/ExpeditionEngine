#include "AudioSystem.h"

AudioSystem* AudioSystem::pInstance = nullptr;

#include "../Scene Components/Audio Emitter/AudioEmitterAttorney.h"

#include "Commands/AudioCommand_Pause.h"
#include "Commands/AudioCommand_Play.h"
#include "Commands/AudioCommand_Stop.h"

#include "Commands/AudioCommand_AcquireEmitterData.h"
#include "Commands/AudioCommand_AcquireEmitterDataStreamed.h"
#include "Commands/AudioCommand_ReleaseEmitterData.h"

#include "Commands/AudioCommand_SetPan.h"
#include "Commands/AudioCommand_SetPitch.h"
#include "Commands/AudioCommand_SetVolume.h"
#include "Commands/AudioCommand_SetVolumeMaster.h"

#include <Xaudio2.h>
#include <Windows.h>

#include <assert.h>

AudioSystem::AudioSystem()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	HRESULT hResult;

	hResult = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(!FAILED(hResult));

	hResult = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	assert(!FAILED(hResult));
	pMasteringVoice->GetVoiceDetails(&voiceDetails);

	DWORD dwChannelMask;
	pMasteringVoice->GetChannelMask(&dwChannelMask);
	X3DAUDIO_HANDLE X3DInstance;
	hResult = X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, X3DInstance);

	
	DSPSettings.SrcChannelCount = 1;
	DSPSettings.DstChannelCount = voiceDetails.InputChannels;
	matrixDSP = new FLOAT32[voiceDetails.InputChannels];
	DSPSettings.pMatrixCoefficients = matrixDSP;
}

AudioSystem::~AudioSystem()
{
	delete matrixDSP;
	pMasteringVoice->DestroyVoice();
	pXAudio2->Release();
	CoUninitialize();
}

void AudioSystem::privAcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pAudioEmitter, AudioEmitterCallback* pCallback, AudioClip& audioClip)
{
	audioCommandQueueMutex.lock();

	AudioCommand_AcquireEmitterData* pTemp = poolAudioCommand_AcquireEmitterData.GetPooledObject();
	pTemp->Initialize(outIterator, pAudioEmitter, pCallback, audioClip);
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

void AudioSystem::privAcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter * pAudioEmitter, AudioEmitterCallback * pCallback, const char * audioFileName)
{
	audioCommandQueueMutex.lock();

	AudioCommand_AcquireEmitterDataStreamed* pTemp = poolAudioCommand_AcquireEmitterDataStreamed.GetPooledObject();
	pTemp->Initialize(outIterator, pAudioEmitter, pCallback, audioFileName);
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

void AudioSystem::privReleaseAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator)
{
	audioCommandQueueMutex.lock();

	AudioCommand_ReleaseEmitterData* pTemp = poolAudioCommand_ReleaseEmitterData.GetPooledObject();
	pTemp->Initialize(outIterator);
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

void AudioSystem::privSetMasterVolume(const float & newMasterVolume)
{
	audioCommandQueueMutex.lock();
	masterVolume = newMasterVolume;

	AudioCommand_SetVolumeMaster* pTemp = poolAudioCommand_SetVolumeMaster.GetPooledObject();
	pTemp->Initialize(newMasterVolume);
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

void AudioSystem::privStopAllSounds()
{
	priorityTable.StopAllSounds();
}

void AudioSystem::privPause(AudioEmitter * const pAudioEmitter)
{
	audioCommandQueueMutex.lock();

	AudioCommand_Pause* pTemp = poolAudioCommand_Pause.GetPooledObject();
	pTemp->Initialize(AudioEmitterAttorney::AudioSystemControl::GetAudioEmitterData(pAudioEmitter));
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

bool AudioSystem::privPlay(AudioEmitter * const pAudioEmitter, const unsigned int& priority, const unsigned int& startingPoint)
{
	bool flag = true;

	audioCommandQueueMutex.lock();

	if (priorityTable.TryRegister(pAudioEmitter, priority))
	{
		AudioCommand_Play* pTemp = poolAudioCommand_Play.GetPooledObject();
		pTemp->Initialize(AudioEmitterAttorney::AudioSystemControl::GetAudioEmitterData(pAudioEmitter), startingPoint);
		commandQueue.Push(pTemp);
	}
	else
	{
		flag = false;
	}

	audioCommandQueueMutex.unlock();

	return flag;
}

void AudioSystem::privStop(AudioEmitter * const pAudioEmitter)
{
	priorityTable.Deregister(pAudioEmitter);
	SubmitStopCommand(pAudioEmitter);
}

void AudioSystem::privSetVolume(PooledResourceIterator<AudioEmitterData>& outIterator, const float & volume)
{
	audioCommandQueueMutex.lock();

	AudioCommand_SetVolume* pTemp = poolAudioCommand_SetVolume.GetPooledObject();
	pTemp->Initialize(outIterator, volume);
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

void AudioSystem::privSetPitch(PooledResourceIterator<AudioEmitterData>& outIterator, const float & targetRatio)
{
	audioCommandQueueMutex.lock();

	AudioCommand_SetPitch* pTemp = poolAudioCommand_SetPitch.GetPooledObject();
	pTemp->Initialize(outIterator, targetRatio);
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

void AudioSystem::privSetPan(PooledResourceIterator<AudioEmitterData>& outIterator, const float & panningValue)
{
	audioCommandQueueMutex.lock();

	AudioCommand_SetPan* pTemp = poolAudioCommand_SetPan.GetPooledObject();
	pTemp->Initialize(outIterator, panningValue);
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

void AudioSystem::privStopForcedByAudioSystem(AudioEmitter * const pAudioEmitter)
{
	SubmitStopCommand(pAudioEmitter);
}

void AudioSystem::privFinalExecution()
{
	privProcessAudioCommands();
}

IXAudio2 * AudioSystem::GetXAudio2()
{
	return pXAudio2;
}

IXAudio2MasteringVoice * AudioSystem::GetMasteringVoice()
{
	return pMasteringVoice;
}

AudioEmitterDataManager & AudioSystem::GetAudioEmitterDataManager()
{
	return audioEmitterDataManager;
}

void AudioSystem::cmdSetMasterVolume(const float & newMasterVolume)
{
	pMasteringVoice->SetVolume(newMasterVolume);
}

void AudioSystem::RecycleAudioCommand(AudioCommand_Pause * pAudioCommand_Pause)
{
	poolAudioCommand_Pause.RecycleObject(pAudioCommand_Pause);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_Play * pAudioCommand_Play)
{
	poolAudioCommand_Play.RecycleObject(pAudioCommand_Play);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_Stop * pAudioCommand_Stop)
{
	poolAudioCommand_Stop.RecycleObject(pAudioCommand_Stop);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_AcquireEmitterData * pAudioCommand_AcquireEmitterData)
{
	poolAudioCommand_AcquireEmitterData.RecycleObject(pAudioCommand_AcquireEmitterData);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_AcquireEmitterDataStreamed * pAudioCommand_AcquireEmitterDataStreamed)
{
	poolAudioCommand_AcquireEmitterDataStreamed.RecycleObject(pAudioCommand_AcquireEmitterDataStreamed);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_ReleaseEmitterData * pAudioCommand_ReleaseEmitterData)
{
	poolAudioCommand_ReleaseEmitterData.RecycleObject(pAudioCommand_ReleaseEmitterData);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_SetPan * pAudioCommand_SetPan)
{
	poolAudioCommand_SetPan.RecycleObject(pAudioCommand_SetPan);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_SetPitch * pAudioCommand_SetPitch)
{
	poolAudioCommand_SetPitch.RecycleObject(pAudioCommand_SetPitch);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_SetVolume * pAudioCommand_SetVolume)
{
	poolAudioCommand_SetVolume.RecycleObject(pAudioCommand_SetVolume);
}

void AudioSystem::RecycleAudioCommand(const AudioCommand_SetVolumeMaster * pAudioCommand_SetVolumeMaster)
{
	poolAudioCommand_SetVolumeMaster.RecycleObject(pAudioCommand_SetVolumeMaster);
}

void AudioSystem::privProcessAudioCommands()
{
	bool hasWork = true;

	//We want to briefly leave the lock open between every execution so that other threads can insert commands while we are working
	while (hasWork)
	{
		audioCommandQueueMutex.lock();

		if (commandQueue.GetSize() > 0)
		{
			pCurrentCommand = commandQueue.Pop();
			pCurrentCommand->Execute(this);
			pCurrentCommand->Recycle(this);
		}
		else
		{
			hasWork = false;
		}

		audioCommandQueueMutex.unlock();
	}
}

void AudioSystem::SubmitStopCommand(AudioEmitter * const pAudioEmitter)
{
	audioCommandQueueMutex.lock();

	AudioCommand_Stop* pTemp = poolAudioCommand_Stop.GetPooledObject();
	pTemp->Initialize(AudioEmitterAttorney::AudioSystemControl::GetAudioEmitterData(pAudioEmitter));
	commandQueue.Push(pTemp);

	audioCommandQueueMutex.unlock();
}

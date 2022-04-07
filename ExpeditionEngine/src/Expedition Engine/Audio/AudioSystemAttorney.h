#pragma once

#include "AudioSystem.h"

class AudioSystemAttorney
{
public:
	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void Initialize()
		{
			AudioSystem::Initialize();
		}

		static void FinalExecution()
		{
			AudioSystem::FinalExecution();
		}

		static void Terminate()
		{
			AudioSystem::Terminate();
		}
	};

	class TaskControl
	{
	private:
		friend class Task_ProcessAudioCommands;
		static void ProcessAudioCommands()
		{
			AudioSystem::ProcessAudioCommands();
		}
	};

	class AudioEmitterControl
	{
	private:
		friend class AudioEmitter;

		static void AcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pAudioEmitter, AudioEmitterCallback* pCallback, AudioClip& audioClip)
		{
			AudioSystem::AcquireAudioEmitterData(outIterator, pAudioEmitter, pCallback, audioClip);
		}
		static void AcquireAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator, AudioEmitter* pAudioEmitter, AudioEmitterCallback* pCallback, const char * audioFileName)
		{
			AudioSystem::AcquireAudioEmitterData(outIterator, pAudioEmitter, pCallback, audioFileName);
		}

		static void ReleaseAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator)
		{
			AudioSystem::ReleaseAudioEmitterData(outIterator);
		}

		static bool TryPlay(AudioEmitter * const pAudioEmitter, const unsigned int& priority, const unsigned int& startingPoint)
		{
			return AudioSystem::Play(pAudioEmitter, priority, startingPoint);
		}
		static void Pause(AudioEmitter * const pAudioEmitter)
		{
			AudioSystem::Pause(pAudioEmitter);
		}
		static void Stop(AudioEmitter * const pAudioEmitter)
		{
			AudioSystem::Stop(pAudioEmitter);
		}
		static void StopForcedByAudioSystem(AudioEmitter * const pAudioEmitter)
		{
			AudioSystem::StopForcedByAudioSystem(pAudioEmitter);
		}

		static void SetVolume(PooledResourceIterator<AudioEmitterData>& pAudioEmitterData, const float& volume)
		{
			AudioSystem::SetVolume(pAudioEmitterData, volume);
		}

		static void SetPitch(PooledResourceIterator<AudioEmitterData>& pAudioEmitterData, const float & targetRatio)
		{
			AudioSystem::SetPitch(pAudioEmitterData, targetRatio);
		}

		static void SetPan(PooledResourceIterator<AudioEmitterData>& pAudioEmitterData, const float& panningValue)
		{
			AudioSystem::SetPan(pAudioEmitterData, panningValue);
		}
	};

	class AudioCommandControl
	{
	private:
		friend class AudioCommand_Pause;
		friend class AudioCommand_Play;
		friend class AudioCommand_Stop;

		friend class AudioCommand_AcquireEmitterData;
		friend class AudioCommand_AcquireEmitterDataStreamed;
		friend class AudioCommand_ReleaseEmitterData;

		friend class AudioCommand_SetPan;
		friend class AudioCommand_SetPitch;
		friend class AudioCommand_SetVolume;
		friend class AudioCommand_SetVolumeMaster;


		static IXAudio2* GetXAudio2(AudioSystem* const pAudioSystem)
		{
			return pAudioSystem->GetXAudio2();
		}

		static IXAudio2MasteringVoice* GetMasteringVoice(AudioSystem* const pAudioSystem)
		{
			return pAudioSystem->GetMasteringVoice();
		}

		static AudioEmitterDataManager& GetAudioEmitterDataManager(AudioSystem* const pAudioSystem)
		{
			return pAudioSystem->GetAudioEmitterDataManager();
		}

		static void cmdSetMasterVolume(AudioSystem* const pAudioSystem, const float& newMasterVolume)
		{
			pAudioSystem->cmdSetMasterVolume(newMasterVolume);
		}

		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_Pause* pAudioCommand_Pause)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_Pause);
		}
		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_Play* pAudioCommand_Play)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_Play);
		}
		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_Stop* pAudioCommand_Stop)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_Stop);
		}

		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_AcquireEmitterData* pAudioCommand_AcquireEmitterData)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_AcquireEmitterData);
		}
		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_AcquireEmitterDataStreamed* pAudioCommand_AcquireEmitterDataStreamed)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_AcquireEmitterDataStreamed);
		}
		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_ReleaseEmitterData* pAudioCommand_ReleaseEmitterData)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_ReleaseEmitterData);
		}

		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_SetPan* pAudioCommand_SetPan)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_SetPan);
		}
		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_SetPitch* pAudioCommand_SetPitch)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_SetPitch);
		}
		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_SetVolume* pAudioCommand_SetVolume)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_SetVolume);
		}
		static void RecycleAudioCommand(AudioSystem* const pAudioSystem, AudioCommand_SetVolumeMaster* pAudioCommand_SetVolumeMaster)
		{
			pAudioSystem->RecycleAudioCommand(pAudioCommand_SetVolumeMaster);
		}
	};

	class AudioEmitterDataControl
	{
	private:
		friend class AudioEmitterData;

		static void ReleaseAudioEmitterData(PooledResourceIterator<AudioEmitterData>& outIterator)
		{
			AudioSystem::ReleaseAudioEmitterData(outIterator);
		}
	};
};
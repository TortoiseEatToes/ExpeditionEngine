#pragma once

#include "AudioClipManager.h"

class AudioClipManagerAttorney
{
public:
	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void Initialize()
		{
			AudioClipManager::Initialize();
		}
		static void Terminate()
		{
			AudioClipManager::Terminate();
		}

	};

	class TaskControl
	{
	private:
		friend class Task_LoadAudioClip;

		static void ReturnTask(Task_LoadAudioClip* const task)
		{
			AudioClipManager::ReturnTask(task);
		}
	};

	class AudioEmitterControl
	{
	private:
		friend class AudioEmitter;

		static AudioClip& GetAudioClip(const AudioClipName& clipName)
		{
			return AudioClipManager::GetAudioClip(clipName);
		}
	};
};
#pragma once

#include "AudioClipCallback_Null.h"
#include "AudioClip.h"

#include "../../../Expedition Resources/AudioSettings.h"
#include "../../Engine/Tasks/Task_LoadAudioClip.h"

#include "../../Containers/Pool.h"

#include <mutex>



class AudioClipManager
{
public:

	static void Load(const AudioClipName& clipName, const std::string& fileName)
	{
		Instance()->privLoad(clipName, fileName, &AudioClipCallback_Null::Instance());
	}

	static void Load(const AudioClipName& clipName, const std::string& fileName, AudioClipCallback* pAudioClipCallback)
	{
		Instance()->privLoad(clipName, fileName, pAudioClipCallback);
	}

	static void LoadAsync(const AudioClipName& clipName, const std::string& fileName)
	{
		Instance()->privLoadAsync(clipName, fileName, &AudioClipCallback_Null::Instance());
	}

	static void LoadAsync(const AudioClipName& clipName, const std::string& fileName, AudioClipCallback* pAudioClipCallback)
	{
		Instance()->privLoadAsync(clipName, fileName, pAudioClipCallback);
	}

private:
	friend class AudioClipManagerAttorney;

	AudioClipManager() = default;
	AudioClipManager(const AudioClipManager& other) = delete;
	AudioClipManager& operator= (const AudioClipManager& other) = delete;
	~AudioClipManager() = default;

	static AudioClipManager* pInstance;
	
	static AudioClipManager* Instance()
	{
		return pInstance;
	}
	static void Initialize()
	{
		pInstance = new AudioClipManager();
	}
	static void Terminate()
	{
		delete pInstance;
	}

	static AudioClip& GetAudioClip(const AudioClipName& clipName){return Instance()->privGetAudioClip(clipName);}
	AudioClip& privGetAudioClip(const AudioClipName& clipName);

	void privLoad(const AudioClipName& clipName, const std::string& fileName, AudioClipCallback* pAudioClipCallback);
	void privLoadAsync(const AudioClipName& clipName, const std::string& fileName, AudioClipCallback* pAudioClipCallback);

	static void ReturnTask(const Task_LoadAudioClip* pTask){Instance()->privReturnTask(pTask);}
	void privReturnTask(const Task_LoadAudioClip* pTask);


	Pool<Task_LoadAudioClip> loadAudioClipTasks;
	AudioClip audioClips[NumberOfAudioClips];
	std::mutex mutex;
	const char* defaultPath = "Assets/Audio/";
};
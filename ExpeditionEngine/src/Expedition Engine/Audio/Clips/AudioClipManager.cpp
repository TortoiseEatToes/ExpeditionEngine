#include "AudioClipManager.h"

AudioClipManager* AudioClipManager::pInstance = nullptr;

AudioClip & AudioClipManager::privGetAudioClip(const AudioClipName & clipName)
{
	return audioClips[clipName];
}

void AudioClipManager::privLoad(const AudioClipName & clipName, const std::string & fileName, AudioClipCallback * pAudioClipCallback)
{
	audioClips[clipName].Load(defaultPath + fileName, pAudioClipCallback);
}

void AudioClipManager::privLoadAsync(const AudioClipName & clipName, const std::string & fileName, AudioClipCallback * pAudioClipCallback)
{
	mutex.lock();
	Task_LoadAudioClip* pTemp = loadAudioClipTasks.GetPooledObject();
	mutex.unlock();
	
	pTemp->Initialize(clipName, fileName, pAudioClipCallback);
	pTemp->ExecuteAsync();
}

void AudioClipManager::privReturnTask(const Task_LoadAudioClip * pTask)
{
	mutex.lock();
	loadAudioClipTasks.RecycleObject(pTask);
	mutex.unlock();
}

#pragma once

#include "EngineTask.h"

#include "../../../Expedition Resources/AudioSettings.h"

class AudioClipCallback;

class Task_LoadAudioClip : public EngineTask
{
public:
	Task_LoadAudioClip();
	Task_LoadAudioClip(const Task_LoadAudioClip& other) = default;
	Task_LoadAudioClip& operator= (const Task_LoadAudioClip& other) = delete;
	~Task_LoadAudioClip() = default;

	void Initialize(const AudioClipName & initclipName, const std::string & initfileName, AudioClipCallback * initpAudioClipCallback);

private:
	void Work() override;
	void OnWorkComplete() override;

	std::string fileName;
	AudioClipCallback * pAudioClipCallback;
	AudioClipName clipName;
};
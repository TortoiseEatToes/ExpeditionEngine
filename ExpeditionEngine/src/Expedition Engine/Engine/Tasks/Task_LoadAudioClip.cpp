#include "Task_LoadAudioClip.h"

#include "../../Audio/Clips/AudioClipManagerAttorney.h"

Task_LoadAudioClip::Task_LoadAudioClip()
	: EngineTask("LoadAudioClip", EngineTask::PriorityLevel::Low)
{
}

void Task_LoadAudioClip::Initialize(const AudioClipName & initclipName, const std::string & initfileName, AudioClipCallback * initpAudioClipCallback)
{
	clipName = initclipName;
	fileName = initfileName;
	pAudioClipCallback = initpAudioClipCallback;
}

void Task_LoadAudioClip::Work()
{
	AudioClipManager::Load(clipName, fileName, pAudioClipCallback);
}

void Task_LoadAudioClip::OnWorkComplete()
{
	AudioClipManagerAttorney::TaskControl::ReturnTask(this);
}

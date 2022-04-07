#include "Task_StreamAudioClip.h"

#include "../../Audio/EmitterData/AudioEmitterBuffer_StreamedAttorney.h"

Task_StreamAudioClip::Task_StreamAudioClip(AudioEmitterBuffer_Streamed * const initAudioEmitterBuffer_Streamed)
	: EngineTask("StreamAudioClip", EngineTask::PriorityLevel::Medium)
{
	pAudioEmitterBuffer_Streamed = initAudioEmitterBuffer_Streamed;
}

void Task_StreamAudioClip::Work()
{
	AudioEmitterBuffer_StreamedAttorney::TaskControl::StreamData(pAudioEmitterBuffer_Streamed);
}

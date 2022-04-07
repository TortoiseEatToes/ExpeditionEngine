#pragma once

#include "EngineTask.h"

class AudioEmitterBuffer_Streamed;

class Task_StreamAudioClip : public EngineTask
{
public:
	Task_StreamAudioClip() = delete;
	Task_StreamAudioClip(AudioEmitterBuffer_Streamed * const initAudioEmitterBuffer_Streamed);
	Task_StreamAudioClip(const Task_StreamAudioClip& other) = delete;
	Task_StreamAudioClip& operator= (const Task_StreamAudioClip& other) = delete;
	~Task_StreamAudioClip() = default;

	

private:
	void Work() override;
	AudioEmitterBuffer_Streamed* pAudioEmitterBuffer_Streamed;
};
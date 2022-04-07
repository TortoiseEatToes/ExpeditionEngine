#pragma once

#include "EngineTask.h"

class AudioSystem;

class Task_ProcessAudioCommands : public EngineTask
{
public:
	Task_ProcessAudioCommands();
	Task_ProcessAudioCommands(const Task_ProcessAudioCommands& other) = delete;
	Task_ProcessAudioCommands& operator= (const Task_ProcessAudioCommands& other) = delete;
	~Task_ProcessAudioCommands() = default;

private:
	void Work() override;
};
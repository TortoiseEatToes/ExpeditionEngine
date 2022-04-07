#pragma once

#include "../Containers/PriorityQueueArray.h"

#include <mutex>

class AudioEmitter;

class AudioPriorityTable
{
public:
	AudioPriorityTable();
	AudioPriorityTable(const AudioPriorityTable& other) = delete;
	AudioPriorityTable& operator= (const AudioPriorityTable& other) = delete;
	~AudioPriorityTable() = default;

	bool TryRegister(AudioEmitter* const pAudioEmitter, const int& priority);
	void Deregister(AudioEmitter* const pAudioEmitter);

	void StopAllSounds();

private:

	void RemoveAudioEmitter();

	PriorityQueueArray<AudioEmitter*, int> priorityQueue;
	std::mutex mutex;
	AudioEmitter* pAudioEmitterRemoved;
};
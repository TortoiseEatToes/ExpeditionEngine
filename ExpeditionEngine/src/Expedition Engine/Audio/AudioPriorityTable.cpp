#include "AudioPriorityTable.h"

#include "../Scene Components/Audio Emitter/AudioEmitterAttorney.h"

#include "../../Expedition Resources/AudioSettings.h"

AudioPriorityTable::AudioPriorityTable()
	: priorityQueue(MaxNumberOfActiveAudioEmitters)
{
}

bool AudioPriorityTable::TryRegister(AudioEmitter * const pAudioEmitter, const int & priority)
{
	bool flag = true;

	mutex.lock();

	//Low levels are considered to be more important
	if (!priorityQueue.Size() > 0 && priorityQueue.PeekFrontPriority() > priority)
	{
		if (priorityQueue.IsFull())
		{
			RemoveAudioEmitter();
		} 
		priorityQueue.Push(priority, pAudioEmitter, AudioEmitterAttorney::PriorityTableControl::GetPriorityTableIterator(pAudioEmitter));
	}
	else
	{
		flag = false;
	}

	mutex.unlock();

	return flag;
}

void AudioPriorityTable::Deregister(AudioEmitter * const pAudioEmitter)
{
	mutex.lock();

	priorityQueue.Remove(AudioEmitterAttorney::PriorityTableControl::GetPriorityTableIterator(pAudioEmitter));

	mutex.unlock();
}

void AudioPriorityTable::StopAllSounds()
{
	mutex.lock();

	while (priorityQueue.Size() > 0)
	{
		RemoveAudioEmitter();
	}

	mutex.unlock();
}

void AudioPriorityTable::RemoveAudioEmitter()
{
	priorityQueue.Pop(pAudioEmitterRemoved);
	AudioEmitterAttorney::PriorityTableControl::StopForcedByAudioSystem(pAudioEmitterRemoved);
}

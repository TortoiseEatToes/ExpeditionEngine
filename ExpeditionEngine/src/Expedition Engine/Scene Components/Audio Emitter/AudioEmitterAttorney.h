#pragma once

#include "AudioEmitter.h"

class AudioEmitterAttorney
{
public:
	class AudioSystemControl
	{
	private:
		friend class AudioSystem;

		static PooledResourceIterator<AudioEmitterData>& GetAudioEmitterData(AudioEmitter* pAudioEmitter)
		{
			return pAudioEmitter->GetAudioEmitterData();
		}
	};

	class PriorityTableControl
	{
	private:
		friend class AudioPriorityTable;

		static PriorityQueueArray<AudioEmitter*, int>::Iterator& GetPriorityTableIterator(AudioEmitter * const pAudioEmitter)
		{
			return pAudioEmitter->GetPriorityTableIterator();
		}

		static void StopForcedByAudioSystem(AudioEmitter * const pAudioEmitter)
		{
			pAudioEmitter->StopForcedByAudioSystem();
		}
	};
};
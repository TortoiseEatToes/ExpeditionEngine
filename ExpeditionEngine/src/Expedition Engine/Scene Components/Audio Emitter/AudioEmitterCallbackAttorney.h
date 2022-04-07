#pragma once

#include "AudioEmitterCallback.h"

class AudioEmitterCallbackAttorney
{
public:
	class VoiceCallbackControls
	{
	private:
		friend class VoiceCallback;

		static void OnAudioBegin(AudioEmitterCallback* pCallback, AudioEmitter& audioEmitter)
		{
			pCallback->OnAudioBegin(audioEmitter);
		}

		static void OnAudioEnd(AudioEmitterCallback* pCallback, AudioEmitter& audioEmitter)
		{
			pCallback->OnAudioEnd(audioEmitter);
		}

		static void OnAudioLoopEnd(AudioEmitterCallback* pCallback, AudioEmitter& audioEmitter)
		{
			pCallback->OnAudioLoopEnd(audioEmitter);
		}

		static void OnAudioError(AudioEmitterCallback* pCallback, AudioEmitter& audioEmitter)
		{
			pCallback->OnAudioError(audioEmitter);
		}
	};
};
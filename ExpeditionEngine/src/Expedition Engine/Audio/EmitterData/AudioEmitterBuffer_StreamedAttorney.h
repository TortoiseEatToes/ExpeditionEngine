#pragma once
#include "AudioEmitterBuffer_Streamed.h"

class AudioEmitterBuffer_StreamedAttorney
{
public:

	class TaskControl
	{
	private:
		friend class Task_StreamAudioClip;

		static void StreamData(AudioEmitterBuffer_Streamed* pAudioEmitterBuffer_Streamed)
		{
			pAudioEmitterBuffer_Streamed->StreamData();
		}
	};
};
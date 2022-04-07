#pragma once

#include "../../Expedition Engine/Scene Components/Audio Emitter/AudioEmitterCallback.h"
#include "../../Expedition Engine/Scene Components/Audio Emitter/AudioEmitter.h"

class Footstep_Callback : public AudioEmitterCallback
{
public:
	void OnAudioEnd(AudioEmitter* const audioEmitter) override 
	{
		audioEmitter->Play(1, 0);
	}
};
#pragma once
#include "AudioCommand.h"

#include "../../Containers/PooledResourceIterator.h"

class AudioEmitterData;

class AudioCommand_SetVolumeMaster : public AudioCommand
{
public:
	AudioCommand_SetVolumeMaster() = default;
	AudioCommand_SetVolumeMaster(const AudioCommand_SetVolumeMaster& other) = delete;
	AudioCommand_SetVolumeMaster& operator= (const AudioCommand_SetVolumeMaster& other) = delete;
	~AudioCommand_SetVolumeMaster() = default;

	void Initialize(const float& initVolume);
	void Execute(AudioSystem * const pAudioSystem) override;
	void Recycle(AudioSystem * const pAudioSystem) override;

private:
	float volume;
};
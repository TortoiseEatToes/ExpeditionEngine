#pragma once

struct IXAudio2MasteringVoice;
struct IXAudio2;
class AudioEmitterDataManager;

class AudioSystem;

class AudioCommand
{
public:
	AudioCommand() = default;
	AudioCommand(const AudioCommand& other) = delete;
	AudioCommand& operator= (const AudioCommand& other) = delete;
	~AudioCommand() = default;

	virtual void Execute(AudioSystem * const pAudioSystem) = 0;
	virtual void Recycle(AudioSystem * const audioSystem) = 0;

};
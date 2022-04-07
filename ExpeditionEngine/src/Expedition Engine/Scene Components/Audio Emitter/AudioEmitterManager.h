#pragma once

class AudioEmitter;

class AudioEmitterManager
{
public:
	AudioEmitterManager() = default;
	AudioEmitterManager(const AudioEmitterManager& other) = delete;
	AudioEmitterManager& operator= (const AudioEmitterManager& other) = delete;
	~AudioEmitterManager() = default;

	void Register(const AudioEmitter& audioEmitter);
	void Deregister(const AudioEmitter& audioEmitter);

private:
};
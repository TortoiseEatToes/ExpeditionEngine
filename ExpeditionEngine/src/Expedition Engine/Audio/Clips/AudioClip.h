#pragma once

#include "../RIFF_Reader.h"
#include <mutex>

class AudioClipCallback;

class AudioClip
{
public:
	AudioClip() = default;
	AudioClip(const AudioClip&) = delete;
	AudioClip& operator= (const AudioClip&) = delete;
	~AudioClip();

	void Load(const std::string& fileName, AudioClipCallback* pCallback);

	void GetWaveFormat(WAVEFORMATEXTENSIBLE*& pWaveFormat);
	void LoadDataIntoBuffer(XAUDIO2_BUFFER& buffer);

private:
	HRESULT LoadAudioBufferFromFile(const std::string& fileName);
	TCHAR* CreateNewTCHAR(const std::string & fileName);

	std::mutex mutex;
	DWORD dwChunkSize;
	WAVEFORMATEXTENSIBLE waveFormatExtensible = { 0 };
	BYTE* pDataBuffer = nullptr;
};
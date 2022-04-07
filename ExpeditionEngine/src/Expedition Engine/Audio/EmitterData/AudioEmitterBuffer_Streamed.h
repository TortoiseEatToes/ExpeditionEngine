#pragma once


//#include "AudioEmitterBuffer.h"

#include "../../Engine/Tasks/Task_StreamAudioClip.h"


#define STREAMING_BUFFER_SIZE 65536
#define MAX_BUFFER_COUNT 3

#include <xaudio2.h>
#include <mutex>
#include <condition_variable>

class AudioEmitterBuffer_Streamed //: public AudioEmitterBuffer
{
public:
	AudioEmitterBuffer_Streamed();
	AudioEmitterBuffer_Streamed(const AudioEmitterBuffer_Streamed& other) = delete;
	AudioEmitterBuffer_Streamed& operator= (const AudioEmitterBuffer_Streamed& other) = delete;
	~AudioEmitterBuffer_Streamed();

	HRESULT LoadFormat(const std::string & fileName);
	void SetSourceVoice(IXAudio2SourceVoice* const pInitSourceVoice);
	HRESULT BeginStreaming();

	/// <summary>Callback for when the XAudio2 thread is finishes a buffer.</summary>
	bool BufferComplete();

	WAVEFORMATEXTENSIBLE* GetWaveFormat();

	void WaitUntilComplete();
	void ForceStop();

private:
	friend class AudioEmitterBuffer_StreamedAttorney;

	/// <summary>Load one buffer into the source voice.</summary>
	void ReadDataChunk();
	void MoveToNextBuffer();

	/// <summary>Call this function to wake up the worker thread if he is sleeping. NEEDS TO BE CALLED INSIDE A MUTEX!</summary>
	void WakeStreamingWorkerThread();

	/// <summary>This function is called by the worker thread.</summary>
	void StreamData();

	TCHAR* CreateNewTCHAR(const std::string & fileName);

	BYTE buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];

	//Gets assinged in LoadFormat
	HANDLE hFile; 
	DWORD dwChunkSize;
	DWORD dwChunkPositionStart;
	DWORD dwChunkPositionCurrent;

	IXAudio2SourceVoice* pSourceVoice;
	std::mutex mutex;
	Task_StreamAudioClip streamingWorkerTask;
	WAVEFORMATEXTENSIBLE waveFormatExtensible = { 0 };
	std::condition_variable conditionalVariable;
	int currentBuffer = 0;
	int buffersToLoad = 0;
	bool isActive = false;
	bool audioIsComplete;
	bool audioEngineIsActive = false;
};
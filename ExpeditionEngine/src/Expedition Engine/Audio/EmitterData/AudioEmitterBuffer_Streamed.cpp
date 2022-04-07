#include "AudioEmitterBuffer_Streamed.h"

#include "../RIFF_Reader.h"
#include <assert.h>

AudioEmitterBuffer_Streamed::AudioEmitterBuffer_Streamed()
	:streamingWorkerTask(this)
{
}

AudioEmitterBuffer_Streamed::~AudioEmitterBuffer_Streamed()
{
	if (isActive)
	{
		CloseHandle(hFile);
	}
}

HRESULT AudioEmitterBuffer_Streamed::LoadFormat(const std::string & fileName)
{
	//Convert the string name to the correct file type
#ifdef _XBOX
	char* strFileName = fileName.c_str;
#else
	TCHAR * strFileName = CreateNewTCHAR(fileName);
#endif

	//--------------------- Open the file ------------------------------------
	hFile = CreateFile(
		strFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
#ifdef _XBOX
	//Do nothing?
#else
	delete strFileName;
#endif

	if (INVALID_HANDLE_VALUE == hFile)
		return HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	//---------------------------------------------------------------------------


	//------------ Locate RIFF chunk and verify the file type is correct ---------------------
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPositionStart);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPositionStart);
	if (filetype != fourccWAVE)
		return S_FALSE;
	//---------------------------------------------------------------------------

	//---------------------- Locate and read the format chunk ----------------------------
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPositionStart);
	ReadChunkData(hFile, &waveFormatExtensible, dwChunkSize, dwChunkPositionStart);
	//---------------------------------------------------------------------------
	return S_OK;
}

void AudioEmitterBuffer_Streamed::SetSourceVoice(IXAudio2SourceVoice * const pInitSourceVoice)
{
	pSourceVoice = pInitSourceVoice;
}

HRESULT AudioEmitterBuffer_Streamed::BeginStreaming()
{
	//---------------- Locate the data chunk ----------------------------
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPositionStart);
	dwChunkPositionCurrent = dwChunkPositionStart;
	//---------------------------------------------------------------------------

	currentBuffer = 0;
	buffersToLoad = 3;
	audioIsComplete = false;

	//Load one chunk so that the AudioEmitter starts with data, and then kick off the streaming thread
	ReadDataChunk();
	WakeStreamingWorkerThread();

	return S_OK;
}

bool AudioEmitterBuffer_Streamed::BufferComplete()
{
	bool flag = false;
	mutex.lock();
	if (!audioIsComplete)
	{
		++buffersToLoad;
		WakeStreamingWorkerThread();
		flag = true;
	}
	mutex.unlock();
	return flag;
}

WAVEFORMATEXTENSIBLE* AudioEmitterBuffer_Streamed::GetWaveFormat()
{
	return &waveFormatExtensible;
}

void AudioEmitterBuffer_Streamed::WaitUntilComplete()
{
	{
		std::unique_lock<std::mutex> lock(mutex);
		conditionalVariable.wait(lock, [this] {return !isActive; });
	}
}

void AudioEmitterBuffer_Streamed::ForceStop()
{
	mutex.lock();
	audioEngineIsActive = false;
	mutex.unlock();

	WaitUntilComplete();
}

void AudioEmitterBuffer_Streamed::ReadDataChunk()
{
	//Load the data chunk
	ReadChunkData(hFile, buffers[currentBuffer], STREAMING_BUFFER_SIZE, dwChunkPositionCurrent);
	dwChunkPositionCurrent += STREAMING_BUFFER_SIZE;

	DWORD remainingSize = dwChunkSize - dwChunkPositionCurrent;
	XAUDIO2_BUFFER buf = { 0 };
	buf.pAudioData = buffers[currentBuffer];
	if (remainingSize < STREAMING_BUFFER_SIZE)
	{
		buf.AudioBytes = remainingSize;
		buf.Flags = XAUDIO2_END_OF_STREAM;
		audioIsComplete = true;
		CloseHandle(hFile);
	}
	else
	{
		buf.AudioBytes = STREAMING_BUFFER_SIZE;
	}
	pSourceVoice->SubmitSourceBuffer(&buf);

	MoveToNextBuffer();
}

void AudioEmitterBuffer_Streamed::MoveToNextBuffer()
{
	++currentBuffer;
	currentBuffer %= MAX_BUFFER_COUNT;
	--buffersToLoad;
}

void AudioEmitterBuffer_Streamed::StreamData()
{
	bool hasWork = true;

	//We want to briefly leave the lock open between every execution so that other threads can insert commands while we are working
	while (hasWork)
	{
		mutex.lock();

		if (buffersToLoad > 0 && audioEngineIsActive)
		{
			ReadDataChunk();
		}
		else
		{
			hasWork = false;
			isActive = false;
			conditionalVariable.notify_all();
		}

		mutex.unlock();
	}
}

void AudioEmitterBuffer_Streamed::WakeStreamingWorkerThread()
{
	//Already mutex protected
	if (!isActive)
	{
		isActive = true;
		audioEngineIsActive = true;
		streamingWorkerTask.ExecuteAsync();
	}
}

TCHAR * AudioEmitterBuffer_Streamed::CreateNewTCHAR(const std::string & fileName)
{
	TCHAR* tempChar = new TCHAR[fileName.size() + 1];
	tempChar[fileName.size()] = 0;

	std::copy(fileName.begin(), fileName.end(), tempChar);

	return tempChar;
}

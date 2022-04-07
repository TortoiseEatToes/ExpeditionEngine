#include "AudioClip.h"

#include "AudioClipCallback.h"

AudioClip::~AudioClip()
{
	delete pDataBuffer;
}

void AudioClip::Load(const std::string & fileName, AudioClipCallback * pCallback)
{
	HRESULT result = LoadAudioBufferFromFile(fileName);

	if (result == S_OK)
	{
		pCallback->OnBufferLoadSuccess();
	}
	else
	{
		pCallback->OnBufferLoadFail();
	}
}

void AudioClip::GetWaveFormat(WAVEFORMATEXTENSIBLE *& pWaveFormat)
{
	mutex.lock();

	pWaveFormat = &waveFormatExtensible;

	mutex.unlock();
}

void AudioClip::LoadDataIntoBuffer(XAUDIO2_BUFFER & buffer)
{
	mutex.lock();
	buffer.AudioBytes = dwChunkSize;
	buffer.pAudioData = pDataBuffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	mutex.unlock();
}

HRESULT AudioClip::LoadAudioBufferFromFile(const std::string& fileName)
{
	//Convert the string name to the correct file type
#ifdef _XBOX
	char* strFileName = fileName.c_str;
#else
	TCHAR * strFileName = CreateNewTCHAR(fileName);
#endif

	mutex.lock();

	//--------------------- Open the file ------------------------------------
	HANDLE hFile = CreateFile(
		strFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	//---------------------------------------------------------------------------


	//------------ Locate RIFF chunk ---------------------
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)
		return S_FALSE;
	//---------------------------------------------------------------------------

	//Locate and read the format chunk
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &waveFormatExtensible, dwChunkSize, dwChunkPosition);
	//---------------------------------------------------------------------------

	//---------------- Locate and read the data chunk ----------------------------
	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);

	//Destroy any memory that was previously stored there
	if (pDataBuffer != nullptr)
	{
		delete pDataBuffer;
	}

	pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	//---------------------------------------------------------------------------
	delete strFileName;
	mutex.unlock();
	return S_OK;
}

TCHAR * AudioClip::CreateNewTCHAR(const std::string & fileName)
{
	TCHAR* tempChar = new TCHAR[fileName.size() + 1];
	tempChar[fileName.size()] = 0;

	std::copy(fileName.begin(), fileName.end(), tempChar);

	return tempChar;
}


#include "AudioEmitterDataManager.h"

AudioEmitterDataManager::AudioEmitterDataManager()
	:audioEmmitterDataPool(100)
{
}

AudioEmitterDataManager::~AudioEmitterDataManager()
{
}

void AudioEmitterDataManager::Acquire(PooledResourceIterator<AudioEmitterData>& outIterator)
{
	audioEmmitterDataPool.AcquireResource(outIterator);
}

void AudioEmitterDataManager::Release(PooledResourceIterator<AudioEmitterData>& outIterator)
{
	outIterator.GetCurrentObject().Sanitize();
	audioEmmitterDataPool.ReleaseResource(outIterator);
}

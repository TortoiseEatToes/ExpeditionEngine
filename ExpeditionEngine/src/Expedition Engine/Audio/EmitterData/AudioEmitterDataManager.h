#pragma once

#include "AudioEmitterData.h"
#include "../../Containers/ResourcePool.h"

class AudioEmitterDataManager
{
public:
	AudioEmitterDataManager();
	AudioEmitterDataManager(const AudioEmitterDataManager& other) = delete;
	AudioEmitterDataManager& operator= (const AudioEmitterDataManager& other) = delete;
	~AudioEmitterDataManager();

	void Acquire(PooledResourceIterator<AudioEmitterData>& outIterator);
	void Release(PooledResourceIterator<AudioEmitterData>& outIterator);

private:
	ResourcePool<AudioEmitterData> audioEmmitterDataPool;
	PooledResourceIterator<AudioEmitterData> iterator;
};
#pragma once

#include "../../Math/Vector/Vector4F.h"

class Vector4FDoubleBufferSynchClean;
class Vector4FDoubleBufferSynchDirty;

class Vector4FDoubleBufferSynchStrategy
{
public:
	Vector4FDoubleBufferSynchStrategy() = default;
	Vector4FDoubleBufferSynchStrategy(const Vector4FDoubleBufferSynchStrategy& other) = delete;
	Vector4FDoubleBufferSynchStrategy& operator= (const Vector4FDoubleBufferSynchStrategy& other) = delete;
	~Vector4FDoubleBufferSynchStrategy() = default;

	virtual void Synchronize(Vector4F& updateBuffer, Vector4F& drawBuffer, Vector4FDoubleBufferSynchClean& pCleanStrategy, Vector4FDoubleBufferSynchDirty& pDirtyStrategy, Vector4FDoubleBufferSynchStrategy*& pCurrentStrategy) = 0;
};
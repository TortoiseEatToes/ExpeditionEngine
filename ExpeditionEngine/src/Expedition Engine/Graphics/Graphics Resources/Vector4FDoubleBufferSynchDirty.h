#pragma once

#include "Vector4FDoubleBufferSynchStrategy.h"

class Vector4FDoubleBufferSynchDirty : public Vector4FDoubleBufferSynchStrategy
{
public:
	Vector4FDoubleBufferSynchDirty() = default;
	Vector4FDoubleBufferSynchDirty(const Vector4FDoubleBufferSynchDirty& other) = delete;
	Vector4FDoubleBufferSynchDirty& operator= (const Vector4FDoubleBufferSynchDirty& other) = delete;
	~Vector4FDoubleBufferSynchDirty() = default;

	void Synchronize(Vector4F& updateBuffer, Vector4F& drawBuffer, Vector4FDoubleBufferSynchClean& pCleanStrategy, Vector4FDoubleBufferSynchDirty& pDirtyStrategy, Vector4FDoubleBufferSynchStrategy*& pCurrentStrategy) override
	{
		drawBuffer = updateBuffer;
		pCurrentStrategy = &pCleanStrategy;
	}
};
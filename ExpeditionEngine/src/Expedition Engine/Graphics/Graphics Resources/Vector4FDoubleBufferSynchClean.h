#pragma once

#include "Vector4FDoubleBufferSynchStrategy.h"

class Vector4FDoubleBufferSynchClean : public Vector4FDoubleBufferSynchStrategy
{
public:
	Vector4FDoubleBufferSynchClean() = default;
	Vector4FDoubleBufferSynchClean(const Vector4FDoubleBufferSynchClean& other) = delete;
	Vector4FDoubleBufferSynchClean& operator= (const Vector4FDoubleBufferSynchClean& other) = delete;
	~Vector4FDoubleBufferSynchClean() = default;

	void Synchronize(Vector4F& updateBuffer, Vector4F& drawBuffer, Vector4FDoubleBufferSynchClean& pCleanStrategy, Vector4FDoubleBufferSynchDirty& pDirtyStrategy, Vector4FDoubleBufferSynchStrategy*& pCurrentStrategy) override
	{
		//Do nothing
	} 
};
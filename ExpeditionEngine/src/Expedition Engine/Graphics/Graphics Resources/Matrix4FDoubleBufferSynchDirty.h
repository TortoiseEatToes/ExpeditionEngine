#pragma once

#include "Matrix4FDoubleBufferSynchStrategy.h"

class Matrix4FDoubleBufferSynchDirty : public Matrix4FDoubleBufferSynchStrategy
{
public:
	Matrix4FDoubleBufferSynchDirty() = default;
	Matrix4FDoubleBufferSynchDirty(const Matrix4FDoubleBufferSynchDirty& other) = delete;
	Matrix4FDoubleBufferSynchDirty& operator= (const Matrix4FDoubleBufferSynchDirty& other) = delete;
	~Matrix4FDoubleBufferSynchDirty() = default;

	void Synchronize(Matrix4F& updateBuffer, Matrix4F& drawBuffer, Matrix4FDoubleBufferSynchClean& pCleanStrategy, Matrix4FDoubleBufferSynchDirty& pDirtyStrategy, Matrix4FDoubleBufferSynchStrategy*& pCurrentStrategy) override
	{
		drawBuffer = updateBuffer;
		pCurrentStrategy = &pCleanStrategy;
	}
};
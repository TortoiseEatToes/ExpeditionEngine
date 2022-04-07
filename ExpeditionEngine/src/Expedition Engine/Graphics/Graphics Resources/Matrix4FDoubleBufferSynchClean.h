#pragma once

#include "Matrix4FDoubleBufferSynchStrategy.h"

class Matrix4FDoubleBufferSynchClean : public Matrix4FDoubleBufferSynchStrategy
{
public:
	Matrix4FDoubleBufferSynchClean() = default;
	Matrix4FDoubleBufferSynchClean(const Matrix4FDoubleBufferSynchClean& other) = delete;
	Matrix4FDoubleBufferSynchClean& operator= (const Matrix4FDoubleBufferSynchClean& other) = delete;
	~Matrix4FDoubleBufferSynchClean() = default;

	void Synchronize(Matrix4F& updateBuffer, Matrix4F& drawBuffer, Matrix4FDoubleBufferSynchClean& pCleanStrategy, Matrix4FDoubleBufferSynchDirty& pDirtyStrategy, Matrix4FDoubleBufferSynchStrategy*& pCurrentStrategy) override
	{
		//Do nothing
	}
};
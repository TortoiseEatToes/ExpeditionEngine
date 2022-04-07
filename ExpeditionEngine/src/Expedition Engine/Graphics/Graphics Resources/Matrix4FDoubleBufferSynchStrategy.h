#pragma once

#include "../../Math/Matrix/Matrix4F.h"

class Matrix4FDoubleBufferSynchClean;
class Matrix4FDoubleBufferSynchDirty;

class Matrix4FDoubleBufferSynchStrategy
{
public:
	Matrix4FDoubleBufferSynchStrategy() = default;
	Matrix4FDoubleBufferSynchStrategy(const Matrix4FDoubleBufferSynchStrategy& other) = delete;
	Matrix4FDoubleBufferSynchStrategy& operator= (const Matrix4FDoubleBufferSynchStrategy& other) = delete;
	~Matrix4FDoubleBufferSynchStrategy() = default;

	virtual void Synchronize(Matrix4F& updateBuffer, Matrix4F& drawBuffer, Matrix4FDoubleBufferSynchClean& pCleanStrategy, Matrix4FDoubleBufferSynchDirty& pDirtyStrategy, Matrix4FDoubleBufferSynchStrategy*& pCurrentStrategy) = 0;
};
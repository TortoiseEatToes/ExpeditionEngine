#include "Matrix4FDoubleBuffer.h"

Matrix4FDoubleBufferSynchClean Matrix4FDoubleBuffer::cleanStrategy;
Matrix4FDoubleBufferSynchDirty Matrix4FDoubleBuffer::dirtyStrategy;

Matrix4FDoubleBuffer::Matrix4FDoubleBuffer(const Matrix4F& startingValue)
	:updateBuffer{ startingValue }, drawBuffer{ startingValue }
{
}

void Matrix4FDoubleBuffer::Synchronize()
{
	pCurrentStrategy->Synchronize(updateBuffer, drawBuffer, cleanStrategy, dirtyStrategy, pCurrentStrategy);
}

void Matrix4FDoubleBuffer::Initialize(const Matrix4F& startingValue)
{
	updateBuffer = startingValue;
	drawBuffer = startingValue;
}
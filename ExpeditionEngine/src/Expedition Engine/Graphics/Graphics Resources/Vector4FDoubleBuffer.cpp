#include "Vector4FDoubleBuffer.h"
#include "../Model/Texture.h"

Vector4FDoubleBufferSynchClean Vector4FDoubleBuffer::cleanStrategy;
Vector4FDoubleBufferSynchDirty Vector4FDoubleBuffer::dirtyStrategy;

Vector4FDoubleBuffer::Vector4FDoubleBuffer(const Vector4F& startingValue)
	:updateBuffer{ startingValue }, drawBuffer{ startingValue }
{
}

void Vector4FDoubleBuffer::Synchronize()
{
	pCurrentStrategy->Synchronize(updateBuffer, drawBuffer, cleanStrategy, dirtyStrategy, pCurrentStrategy);
}

void Vector4FDoubleBuffer::Initialize(const Vector4F& startingValue)
{
	updateBuffer = startingValue;
	drawBuffer = startingValue;
}

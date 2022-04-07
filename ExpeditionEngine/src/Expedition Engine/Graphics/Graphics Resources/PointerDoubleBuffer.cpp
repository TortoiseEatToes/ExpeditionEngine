#include "PointerDoubleBuffer.h"

void PointerDoubleBuffer::Initialize(Texture*& startingValue)
{
	updateBuffer.texture = startingValue;
	drawBuffer.texture = startingValue;
}

void PointerDoubleBuffer::Synchronize()
{
	drawBuffer = updateBuffer;
}
#include "CameraDataDoubleBufferStateDirty.h"

#include "CameraDataDoubleBufferAttorney.h"

void CameraDataDoubleBufferStateDirty::Synchronize(CameraDataDoubleBuffer * const pDoubleBuffer)
{
	CameraDataDoubleBufferAttorney::StateControl::Synchronize(pDoubleBuffer);
}

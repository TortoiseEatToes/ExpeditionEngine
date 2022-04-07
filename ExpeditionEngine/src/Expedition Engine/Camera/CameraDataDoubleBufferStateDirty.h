#pragma once
#include "CameraDataDoubleBufferState.h"

class CameraDataDoubleBufferStateDirty : public CameraDataDoubleBufferState
{
public:
	CameraDataDoubleBufferStateDirty() = default;
	CameraDataDoubleBufferStateDirty(const CameraDataDoubleBufferStateDirty& other) = delete;
	CameraDataDoubleBufferStateDirty& operator= (const CameraDataDoubleBufferStateDirty& other) = delete;
	~CameraDataDoubleBufferStateDirty() = default;

	virtual void Synchronize(CameraDataDoubleBuffer* const pDoubleBuffer) override;
};
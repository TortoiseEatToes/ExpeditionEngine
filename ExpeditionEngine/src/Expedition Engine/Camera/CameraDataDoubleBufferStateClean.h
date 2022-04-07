#pragma once

#include "CameraDataDoubleBufferState.h"

class CameraDataDoubleBufferStateClean : public CameraDataDoubleBufferState
{
public:
	CameraDataDoubleBufferStateClean() = default;
	CameraDataDoubleBufferStateClean(const CameraDataDoubleBufferStateClean& other) = delete;
	CameraDataDoubleBufferStateClean& operator= (const CameraDataDoubleBufferStateClean& other) = delete;
	~CameraDataDoubleBufferStateClean() = default;

	virtual void Synchronize(CameraDataDoubleBuffer* const pDoubleBuffer) override;
};
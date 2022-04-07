#pragma once

class CameraDataDoubleBuffer;

class CameraDataDoubleBufferState
{
public:
	CameraDataDoubleBufferState() = default;
	CameraDataDoubleBufferState(const CameraDataDoubleBufferState& other) = delete;
	CameraDataDoubleBufferState& operator= (const CameraDataDoubleBufferState& other) = delete;
	~CameraDataDoubleBufferState() = default;

	virtual void Synchronize(CameraDataDoubleBuffer* const pDoubleBuffer) = 0;
};
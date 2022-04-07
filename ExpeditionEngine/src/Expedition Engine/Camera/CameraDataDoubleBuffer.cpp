#include "CameraDataDoubleBuffer.h"

CameraDataDoubleBufferStateClean CameraDataDoubleBuffer::cleanState;
CameraDataDoubleBufferStateDirty CameraDataDoubleBuffer::dirtyState;

void CameraDataDoubleBuffer::Initialize(const Camera::Type& type)
{
	updateBuffer.Initialize(type);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::SetType(const Camera::Type& type)
{
	updateBuffer.SetType(type);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::SetPerspective(const float & fieldOfView_Degs, const float & initAspectRatio, const float & initNearDist, const float & initFarDist)
{
	updateBuffer.SetPerspective(fieldOfView_Degs, initAspectRatio, initNearDist, initFarDist);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::SetOrthographic(const float & initXmin, const float & initXmax, const float & initYmin, const float & initYmax, const float & initZmin, const float & initZmax)
{
	updateBuffer.SetOrthographic(initXmin, initXmax, initYmin, initYmax, initZmin, initZmax);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::SetOrientAndPosition(const Vector4F & up_vect, const Vector4F & inLookAt_pt, const Vector4F & pos_pt)
{
	updateBuffer.SetOrientAndPosition(up_vect, inLookAt_pt, pos_pt);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::Update()
{
	updateBuffer.Update();
	pCurrentState = &dirtyState;
}

const Matrix4F & CameraDataDoubleBuffer::GetViewMatrix() const
{
	return updateBuffer.GetViewMatrix();
}

const Matrix4F & CameraDataDoubleBuffer::GetProjMatrix() const
{
	return updateBuffer.GetProjMatrix();
}

void CameraDataDoubleBuffer::GetPosition(Vector4F & outPos) const
{
	updateBuffer.GetPosition(outPos);
}

const Vector4F & CameraDataDoubleBuffer::GetPosition() const
{
	return updateBuffer.GetPosition();
}

const Vector4F & CameraDataDoubleBuffer::GetDirection() const
{
	return updateBuffer.GetDirection();
}

void CameraDataDoubleBuffer::GetUp(Vector4F & outUp) const
{
	updateBuffer.GetUp(outUp);
}

const Vector4F & CameraDataDoubleBuffer::GetRight() const
{
	return updateBuffer.GetRight();
}

const X3DAUDIO_LISTENER & CameraDataDoubleBuffer::GetAudioListener() const
{
	return listener;
}

void CameraDataDoubleBuffer::TranslateLeftRight(const float & delta)
{
	updateBuffer.TranslateLeftRight(delta);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::TranslateFwdBack(const float & delta)
{
	updateBuffer.TranslateFwdBack(delta);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::TiltUpDown(const float & ang)
{
	updateBuffer.TiltUpDown(ang);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::TurnLeftRight(const float & ang)
{
	updateBuffer.TurnLeftRight(ang);
	pCurrentState = &dirtyState;
}

void CameraDataDoubleBuffer::AlignHeightToTerrain(TerrainModel const * terrain, const float& offsetFromTerrain)
{
	updateBuffer.AlignHeightToTerrain(terrain, offsetFromTerrain);
	pCurrentState = &dirtyState;
}

const CameraData & CameraDataDoubleBuffer::GetObserverBuffer() const
{
	return updateBuffer;
}

void CameraDataDoubleBuffer::Synchronize()
{
	pCurrentState->Synchronize(this);
}

void CameraDataDoubleBuffer::StateCall_Synchronize()
{
	observerBuffer = updateBuffer;
	observerBuffer.SynchronizeAudioListener(listener);

	pCurrentState = &cleanState;
}

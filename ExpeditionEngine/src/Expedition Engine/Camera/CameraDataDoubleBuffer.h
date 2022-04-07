#pragma once


#include "CameraDataDoubleBufferStateClean.h"
#include "CameraDataDoubleBufferStateDirty.h"
#include "CameraData.h"

#include <windows.h>
#include <x3daudio.h>

class CameraDataDoubleBuffer
{
public:
	CameraDataDoubleBuffer() = default;
	CameraDataDoubleBuffer(const CameraDataDoubleBuffer& other) = default;
	CameraDataDoubleBuffer& operator= (const CameraDataDoubleBuffer& other) = delete;
	~CameraDataDoubleBuffer() = default;
	

	void Initialize(const Camera::Type& type);

	void SetType(const Camera::Type& type);

	// Setup on single camera
	void SetPerspective(const float& fieldOfView_Degs, const float& initAspectRatio, const float& initNearDist, const float& initFarDist);
	void SetOrthographic(const float& initXmin, const float& initXmax, const float& initYmin, const float& initYmax, const float& initZmin, const float& initZmax);
	void SetOrientAndPosition(const Vector4F &up_vect, const Vector4F &inLookAt_pt, const Vector4F &pos_pt);

	// update camera system
	void Update();

	// Get the matrices for rendering
	const Matrix4F& GetViewMatrix() const;
	const Matrix4F& GetProjMatrix() const;

	// accessors
	void GetPosition(Vector4F &outPos) const;
	const Vector4F& GetPosition() const;
	//void GetDir(Vector4F &outDir) const;
	const Vector4F& GetDirection() const;
	void GetUp(Vector4F &outUp) const;
	//void GetLookAt(Vector4F &outLookAt) const;
	//void GetRight(Vector4F &outRight) const;
	const Vector4F& GetRight() const;

	const X3DAUDIO_LISTENER& GetAudioListener() const;

	void TranslateLeftRight(const float& delta);
	void TranslateFwdBack(const float& delta);
	void TiltUpDown(const float& ang);
	void TurnLeftRight(const float& ang);

	void AlignHeightToTerrain(TerrainModel const * terrain, const float& offsetFromTerrain);

	// Why no SETS for Pos, Dir, Up, LookAt and Right?
	//   They have to be adjusted _together_ in setOrientAndPosition()

	const CameraData& GetObserverBuffer() const;

private:
	friend class CameraDataDoubleBufferAttorney;
	
	void Synchronize();
	void StateCall_Synchronize();

	X3DAUDIO_LISTENER listener;
	CameraData updateBuffer;
	CameraData observerBuffer;

	static CameraDataDoubleBufferStateClean cleanState;
	static CameraDataDoubleBufferStateDirty dirtyState;
	CameraDataDoubleBufferState* pCurrentState = &cleanState;
};
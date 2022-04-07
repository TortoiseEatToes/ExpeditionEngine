#pragma once

#include "../Math/Matrix/Matrix4F.h"
#include "Camera.h"

struct X3DAUDIO_LISTENER;

class CameraData
{
public:
	CameraData() = default;
	CameraData(const CameraData& other) = delete;
	CameraData& operator= (const CameraData& other);
	~CameraData() = default;

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

	void TranslateLeftRight(const float& delta);
	void TranslateFwdBack(const float& delta);
	void TiltUpDown(const float& ang);
	void TurnLeftRight(const float& ang);

	void AlignHeightToTerrain(TerrainModel const * terrain, const float& offsetFromTerrain);

	void SynchronizeAudioListener(X3DAUDIO_LISTENER& listener);

	// Why no SETS for Pos, Dir, Up, LookAt and Right?
	//   They have to be adjusted _together_ in setOrientAndPosition()

private:
	void UpdateProjectionMatrix();
	void UpdateViewMatrix();

	// Converting from OpenGL-style NDC of [-1,1] to DX's [0,1].  See note: https://anteru.net/blog/2011/12/27/1830/
	Matrix4F NDCConvert = Matrix4F(Vector4F(1.0f, 0.0f, 0.0f, 0.0f),
								   Vector4F(0.0f, 1.0f, 0.0f, 0.0f),
								   Vector4F(0.0f, 0.0f, 0.5f, 0.0f),
								   Vector4F(0.0f, 0.0f, 0.5f, 1.0f));

	// Projection Matrix
	Matrix4F	projMatrix;
	Matrix4F	viewMatrix;

	// camera unit vectors (up, dir, right)
	Vector4F	vUp;
	Vector4F	vDir;
	Vector4F	vRight;  // derived by up and dir
	Vector4F	vPos;
	Vector4F	vLookAt;

	// Define the frustum inputs
	float	nearDist;
	float	farDist;
	float	fovy;  // aka view angle along y axis
	float	aspectRatio;

	// Ortho hacks
	float	xMin;
	float	xMax;

	float	yMin;
	float	yMax;

	float	zMin;
	float	zMax;

	Camera::Type camType;
};
#include "CameraData.h"

#include "../Graphics/Terrain/TerrainModel.h"

#include <windows.h>
#include <x3daudio.h>

CameraData & CameraData::operator=(const CameraData & other)
{
	if (this != &other)
	{
		projMatrix = other.projMatrix;
		viewMatrix = other.viewMatrix;

		vUp = other.vUp;
		vDir = other.vDir;
		vRight = other.vRight;
		vPos = other.vPos;
		vLookAt = other.vLookAt;

		nearDist = other.nearDist;
		farDist = other.farDist;
		fovy = other.fovy;
		aspectRatio = other.aspectRatio;

		xMin = other.xMin;
		xMax = other.xMax;

		yMin = other.yMin;
		yMax = other.yMax;

		zMin = other.zMin;
		zMax = other.zMax;

		camType = other.camType;
	}
	return *this;
}

void CameraData::Initialize(const Camera::Type& type)
{
	camType = type;
	xMin = 0.0f;
	xMax = 0.0f;
	yMin = 0.0f;
	yMax = 0.0f;
	zMax = 0.0f;
	zMin = 0.0f;

	this->aspectRatio = 0.0f;
	this->fovy = 0.0f;
	this->nearDist = 0.0f;
	this->farDist = 0.0f;
}

void CameraData::SetType(const Camera::Type& type)
{
	camType = type;
}

void CameraData::SetPerspective(const float & fieldOfView_Degs, const float & initAspectRatio, const float & initNearDist, const float & initFarDist)
{
	this->fovy = fieldOfView_Degs;
	this->aspectRatio = initAspectRatio;
	this->nearDist = initNearDist;
	this->farDist = initFarDist;
}

void CameraData::SetOrthographic(const float & initXmin, const float & initXmax, const float & initYmin, const float & initYmax, const float & initZmin, const float & initZmax)
{
	xMin = initXmin;
	xMax = initXmax;
	yMin = initYmin;
	yMax = initYmax;
	zMax = initZmax;
	zMin = initZmin;
}

void CameraData::SetOrientAndPosition(const Vector4F & up_vect, const Vector4F & inLookAt_pt, const Vector4F & pos_pt)
{
	// Remember the up, dir and right are unit length, and are perpendicular.
	// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
	// Make sure that all vectors are unit vectors.



	this->vLookAt = inLookAt_pt;
	this->vDir = (inLookAt_pt - pos_pt) * -1; // Right-Hand camera: vDir is flipped

	vDir[w] = 0;

	//TODO: MANUAL NORM BC BROKEN
	FLOAT mag = sqrtf(vDir.Dot(vDir));
	this->vDir *= (static_cast<FLOAT>(1 / mag));

	vDir[w] = 0;

	// Clean up the vectors (Right hand rule)
	this->vRight = up_vect.Cross(this->vDir);
	//this->vRight.Norm();
	mag = sqrtf(vRight.Dot(vRight));
	this->vRight *= (static_cast<FLOAT>(1 / mag));

	vRight[w] = 0;

	this->vUp = this->vDir.Cross(this->vRight);
	//this->vUp.Norm();
	mag = sqrtf(vUp.Dot(vUp));
	this->vUp *= (static_cast<FLOAT>(1 / mag));

	vUp[w] = 0;

	this->vPos = pos_pt;
}

void CameraData::Update()
{
	UpdateProjectionMatrix();
	UpdateViewMatrix();
}

const Matrix4F & CameraData::GetViewMatrix() const
{
	return viewMatrix;
}

const Matrix4F & CameraData::GetProjMatrix() const
{
	return projMatrix;
}

void CameraData::GetPosition(Vector4F & outPos) const
{
	outPos = this->vPos;
}

const Vector4F & CameraData::GetPosition() const
{
	return vPos;
}

const Vector4F & CameraData::GetDirection() const
{
	return vDir;
}

void CameraData::GetUp(Vector4F & outUp) const
{
	outUp = this->vUp;
}

void CameraData::UpdateProjectionMatrix()
{
	if (camType == Camera::Type::PERSPECTIVE_3D)
	{
		float d = 1 / tanf(fovy / 2);

		this->projMatrix[f0] = d / aspectRatio;
		this->projMatrix[f1] = 0.0f;
		this->projMatrix[f2] = 0.0f;
		this->projMatrix[f3] = 0.0f;

		this->projMatrix[f4] = 0.0f;
		this->projMatrix[f5] = d;
		this->projMatrix[f6] = 0.0f;
		this->projMatrix[f7] = 0.0f;

		this->projMatrix[f8] = 0.0f;
		this->projMatrix[f9] = 0.0f;
		this->projMatrix[f10] = -(this->farDist + this->nearDist) / (this->farDist - this->nearDist);
		this->projMatrix[f11] = -1.0f;

		this->projMatrix[f12] = 0.0f;
		this->projMatrix[f13] = 0.0f;
		this->projMatrix[f14] = (-2.0f * this->farDist * this->nearDist) / (this->farDist - this->nearDist);
		this->projMatrix[f15] = 0.0f;
	}
	else
	{
		this->projMatrix[f0] = 2.0f / (xMax - xMin);
		this->projMatrix[f1] = 0.0f;
		this->projMatrix[f2] = 0.0f;
		this->projMatrix[f3] = 0.0f;

		this->projMatrix[f4] = 0.0f;
		this->projMatrix[f5] = 2.0f / (yMax - yMin);
		this->projMatrix[f6] = 0.0f;
		this->projMatrix[f7] = 0.0f;

		this->projMatrix[f8] = 0.0f;
		this->projMatrix[f9] = 0.0f;
		this->projMatrix[f10] = 1.0f / (zMin - xMax);
		this->projMatrix[f11] = 0.0f;

		this->projMatrix[f12] = 0.0f;// -(xMax + xMin) / (xMax - xMin);
		this->projMatrix[f13] = 0.0f;//-(yMax + yMin) / (yMax - yMin);
		this->projMatrix[f14] = -(zMin) / (zMin - zMax);
		this->projMatrix[f15] = 1.0f;
	}

	projMatrix = NDCConvert * projMatrix;
	projMatrix.Transpose();
}

void CameraData::UpdateViewMatrix()
{
	// This functions assumes the your vUp, vRight, vDir are still unit
	// And perpendicular to each other

	// Set for DX Right-handed space
	this->viewMatrix[f0] = this->vRight[x];
	this->viewMatrix[f1] = this->vUp[x];
	this->viewMatrix[f2] = this->vDir[x];
	this->viewMatrix[f3] = 0.0f;

	this->viewMatrix[f4] = this->vRight[y];
	this->viewMatrix[f5] = this->vUp[y];
	this->viewMatrix[f6] = this->vDir[y];
	this->viewMatrix[f7] = 0.0f;

	this->viewMatrix[f8] = this->vRight[z];
	this->viewMatrix[f9] = this->vUp[z];
	this->viewMatrix[f10] = this->vDir[z];
	this->viewMatrix[f11] = 0.0f;

	// Apply R^t( -Pos ). Use dot-product with the basis vectors
	this->viewMatrix[f12] = -vPos.Dot(vRight);
	this->viewMatrix[f13] = -vPos.Dot(vUp);
	this->viewMatrix[f14] = -vPos.Dot(vDir);
	this->viewMatrix[f15] = 1.0f;
}

const Vector4F & CameraData::GetRight() const
{
	return vRight;
}

void CameraData::TranslateLeftRight(const float & delta)
{
	vPos += vRight * delta;
}

void CameraData::TranslateFwdBack(const float & delta)
{
	vPos -= vDir * delta;
}

void CameraData::TiltUpDown(const float & ang)
{
	vDir.RotateAxisAngle(vRight, ang);
	SetOrientAndPosition(Vector4F(0.0f, 1.0f, 0.0f), vPos - vDir, vPos);
}

void CameraData::TurnLeftRight(const float & ang)
{
	vDir.RotateAxisAngle(Vector4F(0.0f, 1.0f, 0.0f), ang);
	SetOrientAndPosition(Vector4F(0.0f, 1.0f, 0.0f), vPos - vDir, vPos);
}

void CameraData::AlignHeightToTerrain(TerrainModel const * terrain, const float & offsetFromTerrain)
{
	vPos.Y() = terrain->BarycentrifyHeight(vPos) + offsetFromTerrain;
}

void CameraData::SynchronizeAudioListener(X3DAUDIO_LISTENER & listener)
{
	listener.Position.x = vPos.X();
	listener.Position.y = vPos.Y();
	listener.Position.z = vPos.Z();
}

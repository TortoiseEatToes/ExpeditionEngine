#include "Camera.h"

#include "CameraDataDoubleBuffer.h"

#include "CameraDataManagerAttorney.h"
#include "../Scenes/SceneManagerAttorney.h"
#include "../Scenes/EngineScene.h"

#include <assert.h>
#include <math.h>

Camera::Camera(const Type & type, const SceneName & sceneToExistIn)
{
	registeredScene = sceneToExistIn;

	SceneManagerAttorney::EngineSceneGetter::GetEngineScene(registeredScene).GetCameraManager().AcquireCameraData(this);
	iterator.GetCurrentObject().Initialize(type);
}

Camera::~Camera()
{
	SceneManagerAttorney::EngineSceneGetter::GetEngineScene(registeredScene).GetCameraManager().ReleaseCameraData(this);
}

void Camera::SetType(const Type & type)
{
	iterator.GetCurrentObject().SetType(type);
}

void Camera::SetPerspective(const float & fieldOfView_Degs, const float & initAspectRatio, const float & initNearDist, const float & initFarDist)
{
	iterator.GetCurrentObject().SetPerspective(fieldOfView_Degs, initAspectRatio, initNearDist, initFarDist);
}

void Camera::SetOrthographic(const float & initXmin, const float & initXmax, const float & initYmin, const float & initYmax, const float & initZmin, const float & initZmax)
{
	iterator.GetCurrentObject().SetOrthographic(initXmin, initXmax, initYmin, initYmax, initZmin, initZmax);
}

void Camera::SetOrientAndPosition(const Vector4F & up_vect, const Vector4F & inLookAt_pt, const Vector4F & pos_pt)
{
	iterator.GetCurrentObject().SetOrientAndPosition(up_vect, inLookAt_pt, pos_pt);
}

const Matrix4F & Camera::GetViewMatrix(void) const
{
	return iterator.GetCurrentObject().GetViewMatrix();
}

const Matrix4F & Camera::GetProjMatrix(void) const
{
	return iterator.GetCurrentObject().GetProjMatrix();
}

void Camera::GetPosition(Vector4F &outPos) const
{
	iterator.GetCurrentObject().GetPosition(outPos);
}

const Vector4F & Camera::GetPosition() const
{
	return iterator.GetCurrentObject().GetPosition();
}

const Vector4F& Camera::GetDirection() const
{
	return iterator.GetCurrentObject().GetDirection();
}

//
//void  Camera::GetDir(Vector4F &outDir) const
//{
//	outDir = this->vDir;
//}
//
void  Camera::GetUp(Vector4F &outUp) const
{
	iterator.GetCurrentObject().GetUp(outUp);
}
//
//void Camera::GetLookAt(Vect &outLookAt) const
//{
//	outLookAt = this->vLookAt;
//}
//
//void Camera::GetRight(Vect &outRight) const
//{
//	outRight = this->vRight;
//}

const Vector4F& Camera::GetRight() const
{
	return iterator.GetCurrentObject().GetRight();
}

void Camera::TranslateLeftRight(const float& delta)
{
	iterator.GetCurrentObject().TranslateLeftRight(delta);
}

void Camera::TranslateFwdBack(const float& delta)
{
	iterator.GetCurrentObject().TranslateFwdBack(delta);
}

void Camera::TiltUpDown(const float& ang)
{
	iterator.GetCurrentObject().TiltUpDown(ang);
}

void Camera::TurnLeftRight(const float& ang)
{
	iterator.GetCurrentObject().TurnLeftRight(ang);
}

void Camera::AlignHeightToTerrain(TerrainModel const * terrain, const float& offsetFromTerrain)
{
	iterator.GetCurrentObject().AlignHeightToTerrain(terrain, offsetFromTerrain);
}

void Camera::Update()
{
	iterator.GetCurrentObject().Update();
}

PooledResourceIterator<CameraDataDoubleBuffer>& Camera::GetIterator()
{
	return iterator;
}

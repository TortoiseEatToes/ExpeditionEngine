#include "Shadow.h"
#include "../DXApp/DXApp_12.h"
#include "../../Camera/Camera.h"

Shadow::Shadow() : map(DXApp_12::GetDevice())//, cam()
{
}

Shadow::~Shadow()
{
}

void Shadow::Initialize(const SceneName& sceneName)
{
	pCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D, sceneName);
}

void Shadow::Sanitize()
{
	delete pCamera;
}

void Shadow::SetShadowParameters(const unsigned int& shadowMapSize, const Vector4F& sceneCenter, const float& sceneLength, const Vector4F& direction, const int& inOffset)
{
	map.BuildResources(shadowMapSize, shadowMapSize);

	pCamera->SetType(Camera::Type::ORTHOGRAPHIC_2D);

	pCamera->SetOrthographic(0, sceneLength, 0, sceneLength, 1.0f, 1000.0f);

	Vector4F pos = direction.NormCopy() * (-sceneLength * 0.5f);
	pos.W() = 1.0f;

	pCamera->SetOrientAndPosition(Vector4F(0, 1, 0), sceneCenter, pos);

	pCamera->Update();

	offset = inOffset;
}

void Shadow::SetShadowParameters(const int& shadowMapSize, const float& angle, const float& farDist, const Vector4F& direction, const Vector4F& pos, const int& inOffset)
{
	map.BuildResources(shadowMapSize, shadowMapSize);

	pCamera->SetType(Camera::Type::PERSPECTIVE_3D);

	pCamera->SetPerspective(angle, 1.0f, 1.0f, farDist);

	Vector4F lookAt = pos + direction;

	lookAt.W() = 0;

	pCamera->SetOrientAndPosition(Vector4F(0, 1, 0), lookAt, pos);

	pCamera->Update();

	offset = inOffset;
	
}

void Shadow::UpdateCamera(const Vector4F& direction, const Vector4F& pos, const float& range, const float& exp)
{
	static float cutoffValue = 0.00001f;

	float cutoff = acosf(powf(cutoffValue, 1.0f /exp));

	Vector4F lookAt = pos + direction;

	lookAt.W() = 0;

	pCamera->SetOrientAndPosition(Vector4F(0, 1, 0), lookAt, pos);

	pCamera->SetPerspective(cutoff, 1.0f, 1.0f, range);

	pCamera->Update();
}


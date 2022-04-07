#pragma once

#include "ShadowMap.h"
#include "../../Containers/List.h"

class Vector4F;
enum SceneName;
class Camera;

class Shadow
{
private:

	ShadowMap map;
	Camera* pCamera;

public:
	Shadow(Shadow&&) = delete;
	Shadow(const Shadow&) = delete;
	const Shadow& operator = (Shadow&&) = delete;
	const Shadow& operator = (const Shadow&) = delete;

	Shadow();
	~Shadow();

	void Initialize(const SceneName& sceneName);
	void Sanitize();

	ID3D12Resource1* GetResource() { return map.GetResource(); }
	Camera* GetCamera() { return pCamera; }

	D3D12_VIEWPORT* GetViewPort() { return map.GetViewport(); }
	D3D12_RECT* GetRect() { return map.GetScissorRect(); }

	void SetShadowParameters(const unsigned int& shadowMapSize, const Vector4F& sceneCenter, const float& sceneLength, const Vector4F& dirction, const int& offset);
	void SetShadowParameters(const int& shadowMapSize, const float& angle, const float& farDist, const Vector4F& direction, const Vector4F& pos, const int& inOffset);

	void UpdateCamera(const Vector4F& direction, const Vector4F& pos, const float& range, const float& exp);

	List<Shadow*>::Iterator iterator;

	int offset;
};


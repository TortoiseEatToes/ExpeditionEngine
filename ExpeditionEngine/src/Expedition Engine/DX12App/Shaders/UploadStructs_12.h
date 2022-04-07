#pragma once

#include "../../Math/Matrix/Matrix4F.h"

#include "../../Graphics/Graphics Resources/Buffers/Buffer_DirectionalLight.h"
#include "../../Graphics/Graphics Resources/Buffers/Buffer_PointLight.h"
#include "../../Graphics/Graphics Resources/Buffers/Buffer_SpotLight.h"
#include "../../Graphics/Graphics Resources/Buffers/Buffer_Material.h"

#include "../../../Expedition Resources/TextureSettings.h"

#include "../../Graphics/Light/LightManager.h"

struct Data_PerObject : public Align16
{
	Matrix4F World;
	Matrix4F WorldInv;
	Buffer_Material Mat;
	TextureName textureName;
};

struct Data_PerFrame : public Align16
{
	Buffer_DirectionalLight DirLight[LightManager::MAX_DIRC_LIGHTS];
	Buffer_PointLight PntLightList[LightManager::MAX_POINT_LIGHTS];
	Buffer_SpotLight SptLightList[LightManager::MAX_SPOT_LIGHTS];
	Matrix4F View;
	Matrix4F Projection;
	Vector4F EyePosWorld;
};

struct Data_Shadow : public Align16
{
	Matrix4F View;
	Matrix4F Projection;
};
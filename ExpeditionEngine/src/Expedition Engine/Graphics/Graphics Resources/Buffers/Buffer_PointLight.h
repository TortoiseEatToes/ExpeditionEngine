#pragma once

#include "Buffer_Material.h"

struct Buffer_PointLight {
	Buffer_Material Mat;
	Vector4F Position;
	Vector4F Attenuation;
};
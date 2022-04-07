#pragma once

#include "Buffer_Material.h"

struct Buffer_SpotLight {
	Buffer_Material Mat;
	Vector4F Position;
	Vector4F Attenuation;
	Vector4F Direction;
};
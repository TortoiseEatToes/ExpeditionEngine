#pragma once

#include "../../../Math/Vector/Vector4F.h"

struct Buffer_Material 
{
	Buffer_Material& operator= (const Buffer_Material& other)
	{
		if (this != &other)
		{
			Ambient = other.Ambient;
			Diffuse = other.Diffuse;
			Specular = other.Specular;
		}
		return *this;
	}

	Vector4F Ambient;
	Vector4F Diffuse;
	Vector4F Specular;
};
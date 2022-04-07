#pragma once

#include "../../Math/Matrix/Matrix4F.h"
#include "../Graphics Resources/Buffers/Buffer_Material.h"

struct GO_DataGPU_WorldColor : public Align16
{
	GO_DataGPU_WorldColor& operator= (const GO_DataGPU_WorldColor& other)
	{
		world = other.world;
		color = other.color;
	}

	Matrix4F world;
	Vector4F color;
	Vector4F pad1;
	Vector4F pad2;
	Vector4F pad3;
};

struct GO_DataGPU_World : public Align16
{
	GO_DataGPU_World& operator= (const GO_DataGPU_World& other)
	{
		world = other.world;
		worldInv = other.worldInv;
	}

	Matrix4F world;
	Matrix4F worldInv;
};

struct GO_DataGPU_Color : public Align16
{
	GO_DataGPU_Color& operator= (const GO_DataGPU_Color& other)
	{
		material = other.material;
	}

	Buffer_Material material;
	Vector4F pad1;
};

struct GO_DataGPU_WorldMaterial : public Align16
{
	GO_DataGPU_WorldMaterial& operator= (const GO_DataGPU_WorldMaterial& other)
	{
		world = other.world;
		worldInv = other.worldInv;
		material = other.material;
	}

	Matrix4F world;
	Matrix4F worldInv;
	Buffer_Material material;
	Vector4F pad1;
};

struct GO_DataGPU_Particle : public Align16
{
	GO_DataGPU_Particle& operator= (const GO_DataGPU_Particle& other)
	{
		world = other.world;
		tint = other.tint;
		texture = other.texture;
	}

	Matrix4F world;
	Vector4F tint;
	int texture;
	float padf1;
	float padf2;
	float padf3;
	Vector4F pad2;
	Vector4F pad3;
};
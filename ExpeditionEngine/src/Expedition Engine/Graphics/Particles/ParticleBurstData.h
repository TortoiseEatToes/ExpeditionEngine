#pragma once

#include "../../Math/Vector/Vector4F.h"
#include "../../../Expedition Resources/GraphicsResourcesSettings.h"
#include "../../../Expedition Resources/TextureSettings.h"

struct ParticleBurstData
{
	// -------------- Position Data ------------------------
	float positionXMin = 0.0f;
	float positionXMax = 0.0f;

	float positionYMin = 0.0f;
	float positionYMax = 0.0f;

	float positionZMin = 0.0f;
	float positionZMax = 0.0f;

	//----------------- Velocity Data -----------------------------
	float velocityXMin = 0.0f;
	float velocityXMax = 0.0f;

	float velocityYMin = 0.0f;
	float velocityYMax = 0.0f;

	float velocityZMin = 0.0f;
	float velocityZMax = 0.0f;

	//----------------- Acceleration Data -----------------------------
	float accelerationXMin = 0.0f;
	float accelerationXMax = 0.0f;

	float accelerationYMin = 0.0f;
	float accelerationYMax = 0.0f;

	float accelerationZMin = 0.0f;
	float accelerationZMax = 0.0f;

	//----------------- Color Tint Data -----------------------------
	float colorTintRMin = 0.99f;
	float colorTintRMax = 1.01f;
						  
	float colorTintGMin = 0.99f;
	float colorTintGMax = 1.01f;
						  
	float colorTintBMin = 0.99f;
	float colorTintBMax = 1.01f;
						  
	float colorTintAMin = 0.99f;
	float colorTintAMax = 1.01f;

	//----------------- Particle Burst Data -----------------------------
	float particleLifeMin = 0.0f;
	float particleLifeMax = 1.0f;

	ParticleName particleName;
	TextureName textureName;
	int numberOfParticles = 0;
};
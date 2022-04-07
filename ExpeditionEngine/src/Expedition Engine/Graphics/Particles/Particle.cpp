#include "Particle.h"

#include "ParticleBurstData.h"

#include "../../Math/MathTools.h"

#include <d3d11.h>

#include "../../DX12App/DXApp/DXApp_12.h"
#include "../../DX12App/FrameResources/FrameResourceInstanced.h"
#include "../../GraphicsScene/GraphicsSceneManager.h"
#include "../../GraphicsScene/GraphicsScene.h"

void Particle::Initialize(const ParticleBurstData& burstData)
{
	InitializePosition(burstData);
	InitializeVelocity(burstData);
	InitializeAcceleration(burstData);
	InitializeColorTint(burstData);
	InitializeTexture(burstData);
}

void Particle::ApplyForce(const Vector4F& outsideForce)
{
	acceleration += outsideForce;
}

void Particle::ComputeDX11(const float& timeStep, const Vector4F& cameraPosition)
{
	UpdatePosition(timeStep);
	Billboarding(cameraPosition);
}

void Particle::RenderDX11(D3D11_MAPPED_SUBRESOURCE& mappedResource)
{
	memcpy(mappedResource.pData, &graphicsData, sizeof(GO_DataGPU_Particle));
}

void Particle::ComputeDX12(const float& timeStep, const Vector4F& cameraPosition)
{
	UpdatePosition(timeStep);
	Billboarding(cameraPosition);
}

void Particle::RenderDX12(void*& mappedResource)
{
	memcpy(mappedResource, &graphicsData, sizeof(GO_DataGPU_Particle));
}

void Particle::RenderDX12Sorted(std::list<Particle>& mappedResource)
{

}

void Particle::InitializePosition(const ParticleBurstData& burstData)
{
	graphicsData.world = Matrix4F(IDENTITY);
	graphicsData.world.V3().X() = MathTools::RandomFloatIncludingNegatives(burstData.positionXMin, burstData.positionXMax + upperBoundOffset);
	graphicsData.world.V3().Y() = MathTools::RandomFloatIncludingNegatives(burstData.positionYMin, burstData.positionYMax + upperBoundOffset);
	graphicsData.world.V3().Z() = MathTools::RandomFloatIncludingNegatives(burstData.positionZMin, burstData.positionZMax + upperBoundOffset);
}

void Particle::InitializeVelocity(const ParticleBurstData& burstData)
{
	velocity.X() = MathTools::RandomFloatIncludingNegatives(burstData.velocityXMin, burstData.velocityXMax + upperBoundOffset);
	velocity.Y() = MathTools::RandomFloatIncludingNegatives(burstData.velocityYMin, burstData.velocityYMax + upperBoundOffset);
	velocity.Z() = MathTools::RandomFloatIncludingNegatives(burstData.velocityZMin, burstData.velocityZMax + upperBoundOffset);
}

void Particle::InitializeAcceleration(const ParticleBurstData& burstData)
{
	acceleration.X() = MathTools::RandomFloatIncludingNegatives(burstData.accelerationXMin, burstData.accelerationXMax + upperBoundOffset);
	acceleration.Y() = MathTools::RandomFloatIncludingNegatives(burstData.accelerationYMin, burstData.accelerationYMax + upperBoundOffset);
	acceleration.Z() = MathTools::RandomFloatIncludingNegatives(burstData.accelerationZMin, burstData.accelerationZMax + upperBoundOffset);
}

void Particle::InitializeColorTint(const ParticleBurstData& burstData)
{
	graphicsData.tint.X() = MathTools::RandomFloatIncludingNegatives(burstData.colorTintRMin, burstData.colorTintRMax + upperBoundOffset);
	graphicsData.tint.Y() = MathTools::RandomFloatIncludingNegatives(burstData.colorTintGMin, burstData.colorTintGMax + upperBoundOffset);
	graphicsData.tint.Z() = MathTools::RandomFloatIncludingNegatives(burstData.colorTintBMin, burstData.colorTintBMax + upperBoundOffset);
	graphicsData.tint.W() = MathTools::RandomFloatIncludingNegatives(burstData.colorTintAMin, burstData.colorTintAMax + upperBoundOffset);
}

void Particle::InitializeTexture(const ParticleBurstData& burstData)
{
	graphicsData.texture = burstData.textureName;
}

void Particle::UpdatePosition(const float & timeStep)
{
	velocity += acceleration * timeStep;
	graphicsData.world.V3() += velocity * timeStep;
}

void Particle::Billboarding(const Vector4F& cameraPosition)
{

	dircToCam = cameraPosition - graphicsData.world.V3();
	distFromCamSqr = dircToCam.MagSqr();
	rightAxis = dircToCam.Cross(Vector4F(0.0f, 1.0f, 0.0f, 0.0f));
	upAxis = rightAxis.Cross(dircToCam);

	//Normalize the vectors
	dircToCam.Norm();
	dircToCam.W() = 0.0f;
	
	rightAxis.Norm();
	rightAxis.W() = 0.0f;

	upAxis.Norm();
	upAxis.W() = 0.0f;

	//Set the world to the vectors
	graphicsData.world = (Matrix4F(rightAxis, upAxis,
		dircToCam,
		graphicsData.world.V3()));
}
#pragma once

#include "../../Math/Vector/Vector4F.h"
#include "../GraphicsObjects/GO_Data_GPUObjects.h"

#include <list>

struct D3D11_MAPPED_SUBRESOURCE;

struct ParticleBurstData;

//Owned by the particle manager, used to send CPU particle data to the GPU
class Particle
{
public:
	Particle() = default;
	Particle(const Particle&) = default;
	Particle(Particle&&) = delete;
	Particle& operator=(const Particle&) = delete;
	Particle& operator=(Particle&&) = delete;
	~Particle() = default;

	/// <summary>Use a particleBurstData object to initialize all of this particle's data</summary>
	void Initialize(const ParticleBurstData& burstData);
	
	//This is currently not used.  It may be used if we do force volumes
	void ApplyForce(const Vector4F& outsideForce);

	void ComputeDX11(const float& timeStep, const Vector4F& cameraPosition);
	void RenderDX11(D3D11_MAPPED_SUBRESOURCE& mappedResource);

	void ComputeDX12(const float& timeStep, const Vector4F& cameraPosition);
	void RenderDX12(void*& mappedResource);
	void RenderDX12Sorted(std::list<Particle>& mappedResource);

	GO_DataGPU_Particle& GetData()
	{
		return graphicsData;
	}

	float distFromCamSqr;

private:
	void InitializePosition(const ParticleBurstData& burstData);
	void InitializeVelocity(const ParticleBurstData& burstData);
	void InitializeAcceleration(const ParticleBurstData& burstData);
	void InitializeColorTint(const ParticleBurstData& burstData);
	void InitializeTexture(const ParticleBurstData& burstData);

	//Update the particle position, velocity, and acceleration
	void UpdatePosition(const float& timeStep);
	
	//Update the dircToCam, rightAxis, and upAxis vectors
	void Billboarding(const Vector4F& cameraPosition);

	//Data to be sent to the GPU
	GO_DataGPU_Particle graphicsData;

	//Internal data
	Vector4F velocity;
	Vector4F acceleration;

	//Used for computing math
	Vector4F dircToCam;
	Vector4F rightAxis;
	Vector4F upAxis;
	const float upperBoundOffset = 0.000000001f;
};
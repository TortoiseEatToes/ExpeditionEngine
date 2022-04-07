#pragma once

#include "../../Math/Base/Align16.h"
#include "Vector4FDoubleBuffer.h"

#include "../../Containers/PooledResourceIterator.h"

class Vector4FDoubleBufferManager;

class Material : public Align16
{
public:
	Material() = default;
	~Material() = default;

	Vector4FDoubleBuffer& Ambient();
	Vector4FDoubleBuffer& Diffuse();
	Vector4FDoubleBuffer& Specular();


	/// <summary>Initialize the double buffers after acquiring them. INITIALIZE MUST BE CALLED EVERY TIME YOU ACQUIRE A DOUBLE BUFFER.</summary>
	/// <param name="startingValues">const reference to a vector that the ambient, diffuse, and specular double buffers should be initialized with</param>
	void Initialize(const Vector4F& startingValues);

	/// <summary>Initialize the double buffers after acquiring them. INITIALIZE MUST BE CALLED EVERY TIME YOU ACQUIRE A DOUBLE BUFFER.</summary>
	/// <param name="startingAmbient">const reference to a vector that the ambient double buffer should be initialized with</param>
	/// <param name="startingDiffuse">const reference to a vector that the diffuse double buffer should be initialized with</param>
	/// <param name="startingSpecular">const reference to a vector that the specular double buffer should be initialized with</param>
	void Initialize(const Vector4F& startingAmbient, const Vector4F& startingDiffuse, const Vector4F& startingSpecular);


private:
	friend class MaterialAttorney;
	void AcquireBuffers(Vector4FDoubleBufferManager& vector4FDoubleBufferManager);
	void ReleaseBuffers(Vector4FDoubleBufferManager& vector4FDoubleBufferManager);
	void RegisterForSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager);
	void DeregisterFromSynchronization(Vector4FDoubleBufferManager& vector4FDoubleBufferManager);

	PooledResourceIterator<Vector4FDoubleBuffer> ambient;
	PooledResourceIterator<Vector4FDoubleBuffer> diffuse;
	PooledResourceIterator<Vector4FDoubleBuffer> specular;
};
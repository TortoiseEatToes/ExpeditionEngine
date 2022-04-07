// FlatPlane.h
// Berthiaume Jan 2017

#ifndef _FlatPlane
#define _FlatPlane

#include "Model.h"

struct ID3D11DeviceContext;
struct ID3D11Device;

class FlatPlane : public Model
{
public:
	FlatPlane(const FlatPlane&) = delete;				// Copy constructor
	FlatPlane(Model&&) = delete;                    // Move constructor
	FlatPlane& operator=(const FlatPlane&) & = delete;  // Copy assignment operator
	FlatPlane& operator=(FlatPlane&&) & = delete;       // Move assignment operator
	~FlatPlane();

	FlatPlane(float hrep, float vrep, ID3D12GraphicsCommandList4* cmdList);
};

#endif _FlatPlane

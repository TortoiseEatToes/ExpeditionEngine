#include "FlatPlane.h"
#include "Model.h"


FlatPlane::FlatPlane( float x, float y, ID3D12GraphicsCommandList4* cmdList)
{
	numVerts = 4;
	pStdVerts = new StandardVertex[numVerts];

	numTris = 2;
	pTriList = new TriangleByIndex[numTris];

	center = Vector4F(0, 0, 0, 1);

	//mDevice = DXAppAttorney::GetControls::GetDevice();

	float c =.5;
	radius = c;

	pStdVerts[0].set(-x, 0, -y, 1, 1, 0, 1, 0);
	pStdVerts[1].set(-x, 0,  y, 1, 0, 0, 1, 0);
	pStdVerts[2].set( x, 0,  y, 0, 0, 0, 1, 0);
	pStdVerts[3].set( x, 0, -y, 0, 1, 0, 1, 0);
	
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	privLoadDataToGPU(cmdList);
}

FlatPlane::~FlatPlane()
{
}
#include "SpriteModel.h"
#include "Model.h"
#include "../../DX12App/d3dUtil_12.h"

SpriteModel::SpriteModel(float length, float width, ID3D12GraphicsCommandList4* cmdList)
{

	pStdVerts = new StandardVertex[4];

	pStdVerts[0].meshNum = 0;
	pStdVerts[1].meshNum = 0;
	pStdVerts[2].meshNum = 0;
	pStdVerts[3].meshNum = 0;

	pStdVerts[0].u = 0;
	pStdVerts[1].u = 1;
	pStdVerts[2].u = 0;
	pStdVerts[3].u = 1;
	 
	pStdVerts[0].v = 0;
	pStdVerts[1].v = 0;
	pStdVerts[2].v = 1;
	pStdVerts[3].v = 1;
	 

	float halfW = width * .5f;
	float halfH = length * .5f;

	pStdVerts[0].Pos = Vector4F(-halfW, -halfH, 0, 1);
	pStdVerts[1].Pos = Vector4F(halfW, -halfH, 0, 1);
	pStdVerts[2].Pos = Vector4F(-halfW, halfH, 0, 1);
	pStdVerts[3].Pos = Vector4F(halfW, halfH, 0, 1);

	pStdVerts[0].normal = Vector4F(0, 0, 1, 0);
	pStdVerts[1].normal = Vector4F(0, 0, 1, 0);
	pStdVerts[2].normal = Vector4F(0, 0, 1, 0);
	pStdVerts[3].normal = Vector4F(0, 0, 1, 0);

	pTriList = new TriangleByIndex[2];

	pTriList[0].set(0, 2, 1);
	pTriList[1].set(1,2,3);

	numVerts = 4;
	numTris = 2;

	//mDevice = DXAppAttorney::GetControls::GetDevice();

	privLoadDataToGPU(cmdList);
}

SpriteModel::~SpriteModel()
{
}

#include "SkyBox.h"
#include "Model.h"
#include "../../DX12App/d3dUtil_12.h"

SkyBox::SkyBox(float length, float width, float height, ID3D12GraphicsCommandList4* cmdList)
{
	numVerts = 24;
	pStdVerts = new StandardVertex[numVerts];
	numTris = 12;
	pTriList = new TriangleByIndex[numTris];

	if (length > width) {
		if (length > height)
			radius = length;
		else
			radius = height;

	}
	else {
		if (width > height)
			radius = width;
		else
			radius = height;
	}

	center = Vector4F(0, 0, 0, 1);

	int vint = 0;
	int tint = 0;

	const float onethird = (1.0f / 3.0f);
	const float twothird = (2.0f / 3.0f);

	//mDevice = DXAppAttorney::GetControls::GetDevice();

	//back
	pStdVerts[vint++].set(+0.5f*width, +0.5f*height, +0.5f*length, .25, onethird, 0, 0, -1); //BackTL 0
	pStdVerts[vint++].set(-0.5f*width, +0.5f*height, +0.5f*length, .5, onethird , 0, 0, -1);//BackTR 1
	pStdVerts[vint++].set(+0.5f*width, -0.5f*height, +0.5f*length, .25, twothird, 0, 0, -1);//BackBL 2
	pStdVerts[vint++].set(-0.5f*width, -0.5f*height, +0.5f*length, .5, twothird, 0, 0, -1);//BackBR 3

	pTriList[tint++].set(0, 3, 1);
	pTriList[tint++].set(0, 2, 3);

	//left
	pStdVerts[vint++].set(+0.5f*width, +0.5f*height, +0.5f*length, .25, onethird, -1, 0, 0); //BackTL 4
	pStdVerts[vint++].set(+0.5f*width, -0.5f*height, +0.5f*length, .25, twothird, -1, 0, 0);//BackBL 5
	pStdVerts[vint++].set(+0.5f*width, +0.5f*height, -0.5f*length, 0, onethird, -1, 0, 0);//LeftFT 6
	pStdVerts[vint++].set(+0.5f*width, -0.5f*height, -0.5f*length, 0, twothird, -1, 0, 0);//LeftFB 7

	pTriList[tint++].set(6, 5, 4);
	pTriList[tint++].set(6, 7, 5);

	//right
	pStdVerts[vint++].set(-0.5f*width, +0.5f*height, +0.5f*length, .5, onethird, 1, 0, 0);//BackTR 8
	pStdVerts[vint++].set(-0.5f*width, -0.5f*height, +0.5f*length, .5, twothird, 1, 0, 0);//BackBR 9
	pStdVerts[vint++].set(-0.5f*width, +0.5f*height, -0.5f*length, .75, onethird, 1, 0, 0);//RightFt 10
	pStdVerts[vint++].set(-0.5f*width, -0.5f*height, -0.5f*length, .75, twothird, 1, 0, 0);//RightFB 11

	pTriList[tint++].set(8, 11, 10);
	pTriList[tint++].set(8, 9, 11);
	
	//front
	pStdVerts[vint++].set(-0.5f*width, +0.5f*height, -0.5f*length, .75, onethird, 0, 0, 1);//RightFt 12
	pStdVerts[vint++].set(-0.5f*width, -0.5f*height, -0.5f*length, .75, twothird, 0, 0, 1);//RightFB 13
	pStdVerts[vint++].set(+0.5f*width, +0.5f*height, -0.5f*length, 1, onethird, 0, 0, 1);//FrontTR 14
	pStdVerts[vint++].set(+0.5f*width, -0.5f*height, -0.5f*length, 1, twothird, 0, 0, 1);//FrontBR 15

	pTriList[tint++].set(12, 15, 14);
	pTriList[tint++].set(12, 13, 15);

	//top
	pStdVerts[vint++].set(+0.5f*width, +0.5f*height, +0.5f*length, .25, onethird, 0, -1, 0); //BackTL 16
	pStdVerts[vint++].set(-0.5f*width, +0.5f*height, +0.5f*length, .5, onethird, 0, -1, 0);//BackTR 17
	pStdVerts[vint++].set(+0.5f*width, +0.5f*height, -0.5f*length, .25, 0, 0, -1, 0);//TopFL 18
	pStdVerts[vint++].set(-0.5f*width, +0.5f*height, -0.5f*length, .5, 0, 0, -1, 0);//TopFR 19

	pTriList[tint++].set(18, 17, 19);
	pTriList[tint++].set(18, 16, 17);

	//bottom
	pStdVerts[vint++].set(+0.5f*width, -0.5f*height, +0.5f*length, .25, twothird, 0, 1, 0);//BackBL 20
	pStdVerts[vint++].set(-0.5f*width, -0.5f*height, +0.5f*length, .5, twothird, 0, 1, 0);//BackBR 21
	pStdVerts[vint++].set(+0.5f*width, -0.5f*height, -0.5f*length, .25, 1, 0, 1, 0);//BottomFL 22
	pStdVerts[vint++].set(-0.5f*width, -0.5f*height, -0.5f*length, .5, 1, 0, 1, 0);//BottomFR 23

	pTriList[tint++].set(20, 23, 21);
	pTriList[tint++].set(20, 22, 23);

	privLoadDataToGPU(cmdList);
}

SkyBox::~SkyBox()
{
}

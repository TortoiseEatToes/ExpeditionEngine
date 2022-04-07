#include "ModelTools.h"
//#include "Enum.h"
#include <math.h>
#include <assert.h>
#include "Model.h"
#include "../../DX12App/d3dUtil_12.h"



/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{

	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, 0, 0, -1, -1, -1);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, 0, 0, -1, +1, -1);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, 0, 0, +1, +1, -1);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, 0, 0, +1, -1, -1);
	pVerts[4].set(-0.5f, -0.5f, +0.5f, 0, 0, -1, -1, +1);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, 0, 0, -1, +1, +1);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, 0, 0, +1, +1, +1);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, 0, 0, +1, -1, +1);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 14;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	int vint = 0;

	pVerts[vint++].set(0.5f, 0.5f, 0.5f, .25, .625); //FTL 0
	pVerts[vint++].set(-0.5f, 0.5f, 0.5f, .25, .375);  //RTF 1
	pVerts[vint++].set(0.5f, 0.5f, -0.5f, .5, .625); // BLT 2
	pVerts[vint++].set(-0.5f, 0.5f, -0.5f, .5, .375); //BTR 3

	pVerts[vint++].set(-0.5f, -0.5f, 0.5f, 0, .375); //F left 4
	pVerts[vint++].set(0.5f, -0.5f, 0.5f, 0, .625); // F right 5

	pVerts[vint++].set(-0.5f, -0.5f, -0.5f, .75, .375); // B/Bot Upper 6
	pVerts[vint++].set(0.5f, -0.5f, -0.5f, .75, .625); // B Bot Lower 7

	pVerts[vint++].set(0.5f, -0.5f, 0.5f, .25, .875); //L left 8
	pVerts[vint++].set(0.5f, -0.5f, -0.5f, .5, .875); //L right 9

	pVerts[vint++].set(-0.5f, -0.5f, -0.5f, .5, .125); //R left 10
	pVerts[vint++].set(-0.5f, -0.5f, 0.5f, .25, .125); // R right 11

	pVerts[vint++].set(0.5f, -0.5f, 0.5f, 1, .625); //Bot right 12
	pVerts[vint++].set(-0.5f, -0.5f, 0.5f, 1, .375); //Bot left 13

	int tint = 0;

	//top
	pTriList[tint++].set(3, 1, 2);
	pTriList[tint++].set(2, 1, 0);

	//front
	pTriList[tint++].set(1, 4, 0);
	pTriList[tint++].set(4 , 5, 0);

	//left
	pTriList[tint++].set(0,8,9);
	pTriList[tint++].set(0,9,2);

	//right
	pTriList[tint++].set(1,3,11);
	pTriList[tint++].set(3,10,11);

	//back
	pTriList[tint++].set(3,2,7);
	pTriList[tint++].set(7,6,3);

	//Bottom
	pTriList[tint++].set(12,13,6);
	pTriList[tint++].set(12,6,7);
}


void ModelTools::CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	// back face

	pVerts[0].set(0.0f, +0.5f, 0.0f, 0, 0, 0, .5, -1);
	pVerts[1].set(-0.5f, -0.5f, -0.5f, 0, 0, 0, .5, -1);
	pVerts[2].set(+0.5f, -0.5f, -0.5f, 0, 0, 0, .5, -1);
	pTriList[0].set(0, 2, 1);

	// front face
	pVerts[3].set(0.0f, +0.5f, 0.0f, 0, 0, 0, .5, 1);
	pVerts[4].set(+0.5f, -0.5f, +0.5f, 0, 0, 0, .5, 1);
	pVerts[5].set(-0.5f, -0.5f, +0.5f, 0, 0, 0, .5, 1);
	pTriList[1].set(3, 5, 4);

	// left face
	pVerts[6].set(0.0f, +0.5f, 0.0f, 0, 0, 1, .5, 0);
	pVerts[7].set(+0.5f, -0.5f, -0.5f, 0, 0, 1, .5, 0);
	pVerts[8].set(+0.5f, -0.5f, +0.5f, 0, 0, 1, .5, 0);
	pTriList[2].set(6, 8, 7);

	// right face
	pVerts[9].set(0.0f, +0.5f, 0.0f, 0, 0, -1, .5, 0);
	pVerts[10].set(-0.5f, -0.5f, -0.5f, 0, 0, -1, .5, 0);
	pVerts[11].set(-0.5f, -0.5f, +0.5f, 0, 0, -1, .5, 0);
	pTriList[3].set(9, 10, 11);

	// bottom faces
	pVerts[12].set(-0.5f, -0.5f, -0.5f, 0, 0, 0, -1, 0);
	pVerts[13].set(+0.5f, -0.5f, -0.5f, 0, 0, 0, -1, 0);
	pVerts[14].set(+0.5f, -0.5f, +0.5f, 0, 0, 0, -1, 0);
	pVerts[15].set(-0.5f, -0.5f, +0.5f, 0, 0, 0, -1, 0);
	pTriList[4].set(12, 13, 14);
	pTriList[5].set(12, 14, 15);

}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	const float PI = 3.1415926536f;

	nverts = vslice * hslice + 2;
	pVerts = new StandardVertex[nverts];
	ntri = vslice * hslice * 2;
	pTriList = new TriangleByIndex[ntri];

	float deltaTheta = PI / (vslice + 1);
	float deltaPhi = 2 * PI / hslice;

	float theta = 0;
	float phi = 0;

	//-------------------------------
	//vertex and triangles for one pole
	//--------------------------------
	pVerts[0].set(1.0f, 0.0f, 0.0f, 0, 0, 1, 0, 0);

	for (int i = 1; i < hslice; i++) {
		pTriList[i].set(0, i + 1, i);
	}
	pTriList[0].set(0, 1, hslice);

	//-------------------------
	//middle vertices
	//-----------------------

	for (int i = 0; i < vslice; i++) {
		theta = (i + 1)*deltaTheta;

		for (int j = 0; j < hslice; j++) {
			phi = (j + 1) * deltaPhi;

			float x = cosf(theta);
			float y = sinf(phi)*sinf(theta);
			float z = sinf(theta)*cosf(phi);
			pVerts[i*hslice + j + 1].set(x, y, z, 0, 0, x, y, z);
		}

	}

	//--------------------------
	//middle indices
	//----------------------------

	for (int i = 1; i < vslice; i++) {
		pTriList[hslice*(i * 2) - 1].set(hslice*i, hslice*(i - 1) + 1, hslice*(i + 1));
		pTriList[hslice*(i * 2 + 1) - 1].set(hslice*i + 1, hslice*(i + 1), hslice*(i - 1) + 1);


		for (int j = 0; j < hslice - 1; j++) {
			pTriList[hslice*(i * 2 - 1) + j].set(hslice*(i - 1) + j + 1, hslice*(i - 1) + j + 2, hslice*(i)+j + 1);
			pTriList[hslice*(i * 2) + j].set(hslice*(i)+j + 2, hslice*(i)+j + 1, hslice*(i - 1) + j + 2);
		}
	}


	//-------------------------------------
	//vertex and indices for end pole
	//-------------------------------------

	pVerts[nverts - 1].set(-1.0f, 0.0f, 0.0f, 0, 0, -1, 0, 0);


	for (int i = 1; i < hslice; i++) {
		pTriList[ntri - i].set(nverts - 1, nverts - 2 - i, nverts - 1 - i);
	}

	pTriList[ntri - hslice].set(nverts - 1, nverts - 2, nverts - 1 - hslice);

}


void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri, const float& width, const float& height, const float& depth)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	float w = width * 0.5f;
	float h = height * 0.5f;
	float d = depth * 0.5f;


	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(w, h, d, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-w,  h, d, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-w, -h, d, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set( w, -h, d, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(w, h, -d, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-w,  h, -d, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-w, -h, -d, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set( w, -h, -d, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(    w,  h, -d, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(w,  h,  d, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(w, -h,  d, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(w, -h, -d, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(    -w,  h,  d, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-w,  h, -d, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-w, -h, -d, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-w, -h,  d, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(     w, h, -d, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-w, h, -d, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-w, h,  d, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set( w, h,  d, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(     w, -h,  d, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-w, -h,  d, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-w, -h, -d, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set( w, -h, -d, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

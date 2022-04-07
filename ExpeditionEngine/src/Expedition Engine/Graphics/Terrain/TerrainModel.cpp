#include "TerrainModel.h"
#include "../Model/Model.h"
#include "../../DX12App/d3dUtil_12.h"
#include "../../DX12App/Model/DDSTextureLoader.h"
#include <assert.h>
#include "../../Tools/Math.h"
#include "Tools/TerrainCell.h"
#include "../../Math/Vector/Vector4F.h"
#include <fstream>

typedef union PixelInfo
{
	std::uint32_t Colour;
	struct
	{
		std::uint8_t R, G, B, A;
	};
} *PPixelInfo;

TerrainModel::TerrainModel(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, ID3D12GraphicsCommandList4* cmdList)
{
	this->ReadFile(heightmapFile);

	assert(height == width);

	side = height;	// the image should be square

	length = len;
	cellWidth = len / (side - 1);
	invCellWidth = 1/cellWidth;

	int nverts = side * side;
	StandardVertex* pVerts = new StandardVertex[nverts];
	int ntri = (side - 1)*(side - 1) * 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	Vector4F* pTriNorms = new Vector4F[ntri];

	int vint = 0;
	int tint = 0;

	float x = len * .5f; //X position of the most positive X vertex
	float y = ytrans;
	float z = x; //X position of the most positive z vertex

	const int RGBMAX = 256;

	// create verts (side * side)

	for (int i = 0; i < static_cast<int>(side); i++) {

		for (int j = 0; j < static_cast<int>(side); j++) {

			//for all verts:

			uint8_t h_val = pixels[TexelIndex(i, j)]; //find height value/darkness of the pixel

			y = ytrans + static_cast<float>(h_val) / RGBMAX * maxheight; // calculate the height using the max y value, the color value, and the base y value

			pVerts[vint++].set(x, y, z, (i / (static_cast<float>(side) - 1))*RepeatU, (j / (static_cast<float>(side) - 1))*RepeatV); //set the vert to have the found x,y,z coors and the correct U/V coors
			z -= cellWidth; //move to next column


		}

		//For Every row of Verts :
		x -= cellWidth; //Move down a row
		z = len * .5f; //reset to beginning of rpw
	}

	int TopLeftCoor;
	int BottomRightCoor;
	int TopRightCoor;
	int BottomLeftCoor;

	float min;
	float max;

	//create Triangles ((side-1)*(side-1)*2)
	//create cells ((side-1)*(side-1))

	CollisionAABBCollection = new TerrainCell[side*side];

	for (int i = 0; i < static_cast<int>(side) - 1; i++) {
		//for every row of square cells

		for (int j = 0; j < static_cast<int>(side) - 1; j++) {

			//For every cell

			TopLeftCoor = PointtoVert(i, j);
			BottomRightCoor = PointtoVert(i + 1, j + 1);
			TopRightCoor = PointtoVert(i + 1, j);
			BottomLeftCoor = PointtoVert(i, j + 1);

			//Create both triangles for the cell
			pTriNorms[tint] = getTriNorm(pVerts[TopLeftCoor].Pos, pVerts[BottomRightCoor].Pos, pVerts[TopRightCoor].Pos);
			pTriList[tint++].set(TopLeftCoor, BottomRightCoor, TopRightCoor);

			pTriNorms[tint] = getTriNorm(pVerts[TopLeftCoor].Pos, pVerts[BottomLeftCoor].Pos, pVerts[BottomRightCoor].Pos);
			pTriList[tint++].set(TopLeftCoor, BottomLeftCoor, BottomRightCoor);

			//Find max and min y positions
			max = pVerts[TopLeftCoor].Pos.Y();
			max = Math::GetMax(max, pVerts[BottomRightCoor].Pos.Y());
			max = Math::GetMax(max, pVerts[TopRightCoor].Pos.Y());
			max = Math::GetMax(max, pVerts[BottomLeftCoor].Pos.Y());

			min = pVerts[TopLeftCoor].Pos.Y();
			min = Math::GetMin(min, pVerts[BottomRightCoor].Pos.Y());
			min = Math::GetMin(min, pVerts[TopRightCoor].Pos.Y());
			min = Math::GetMin(min, pVerts[BottomLeftCoor].Pos.Y());


			CollisionAABBCollection[TopLeftCoor].MaxY = max;
			CollisionAABBCollection[TopLeftCoor].MinY = min;
			CollisionAABBCollection[TopLeftCoor].coor.i = i;
			CollisionAABBCollection[TopLeftCoor].coor.j = j;

		}
	}

	//Create normals

	for (int j = 0; j < static_cast<int>(side) - 1; j++) {
		pVerts[PointtoVert(0, j)].normal = pTriNorms[PointtoVert(0, j)];
		pVerts[PointtoVert(0, j)].normal[W] = 1.0f;
	}

	for (int j = 0; j < static_cast<int>(side)-1; j++) {
		pVerts[PointtoVert(static_cast<int>(side)-1, j)].normal = pTriNorms[PointtoVert(static_cast<int>(side) - 2, j)];
		pVerts[PointtoVert(static_cast<int>(side)-1, j)].normal[W] = 1.0f;
	}

	for (int i = 1; i < static_cast<int>(side)-1; i++) {
		pVerts[PointtoVert(i, 0)].normal = pTriNorms[PointtoVert(i, 0)];
		pVerts[PointtoVert(i, 0)].normal[W] = 1.0f;
	}

	for (int i = 0; i < static_cast<int>(side)-1; i++) {
		pVerts[PointtoVert(i, static_cast<int>(side)-1)].normal = pTriNorms[PointtoVert(i, static_cast<int>(side)-2)];
		pVerts[PointtoVert(i, static_cast<int>(side)-1)].normal[W] = 1.0f;
	}

	pVerts[PointtoVert(static_cast<int>(side) - 1, static_cast<int>(side) - 1)].normal = pTriNorms[PointtoVert(static_cast<int>(side) - 2, static_cast<int>(side) - 2)];

	

	for (int i = 1; i < static_cast<int>(side) - 1; i++) {

		for (int j = 1; j < static_cast<int>(side) - 1; j++) {

			int vert = (j-1) * 2 + (side - 1)*2*(i-1);

			Vector4F n = (pTriNorms[vert] + pTriNorms[vert + 1] + pTriNorms[vert + 2] + pTriNorms[vert + ((side-1) * 2)] + pTriNorms[vert + ((side-1) * 2) + 2] + pTriNorms[vert + ((side-1) * 2) + 3]);

			n.Norm();

			pVerts[PointtoVert(i, j)].normal = n;
			pVerts[PointtoVert(i, j)].normal[W] = 1.0f;

		}
	}

	//Create model with created verteces and triangles
	pModTerrain = new Model(pVerts, nverts, pTriList, ntri, cmdList);

	delete[] pVerts;
	delete[] pTriList;
	delete[] pTriNorms;
}

TerrainModel::~TerrainModel() {
	delete pModTerrain;
	delete CollisionAABBCollection;
}

Vector4F TerrainModel::BarycentrifyNormal(const Vector4F& pos) {

	TerrainCell cell = CollisionAABBCollection[PosToCellNum(pos)];

	//Get the World Space positions of the for corners of the terrain cell
	StandardVertex PosTopLeft = pModTerrain->GetVert(PointtoVert(cell.coor.i, cell.coor.j));                //Cell farthest in +X,+Z
	StandardVertex PosTopRight = pModTerrain->GetVert(PointtoVert(cell.coor.i + 1, cell.coor.j));			//Cell in the -X,+Z position
	StandardVertex PosBottomLeft = pModTerrain->GetVert(PointtoVert(cell.coor.i, cell.coor.j + 1));			//Cell in the +X, -Z position
	StandardVertex PosBottomRight = pModTerrain->GetVert(PointtoVert(cell.coor.i + 1, cell.coor.j + 1));	// Cell in the farthest -X, -Z position

	Vector4F Normal;


	Vector4F v2 = pos - PosBottomRight.Pos;

	if (v2[x] > v2[z]) {

		float beta = v2[x] * invCellWidth; //invCellWidth is the inverse of the cell width (1/cellWidth) which is calculated once on create for speed.
		float gamma = v2[z] * invCellWidth;

		Normal = PosBottomRight.normal + (beta * (PosBottomLeft.normal - PosBottomRight.normal)) + (gamma * (PosTopLeft.normal- PosBottomLeft.normal));
	}
	else {

		float beta = v2[z] * invCellWidth;
		float gamma = v2[x] * invCellWidth;

		Normal = PosBottomRight.normal + (beta * (PosTopRight.normal - PosBottomRight.normal)) + (gamma * (PosTopLeft.normal - PosTopRight.normal));
	}

	return Normal;
}

float TerrainModel::BarycentrifyHeight(const Vector4F& pos) const
{
	TerrainCell cell = CollisionAABBCollection[PosToCellNum(pos)];

	//Get the World Space positions of the for corners of the terrain cell
	Vector4F PosTopLeft = pModTerrain->GetVertPos(PointtoVert(cell.coor.i, cell.coor.j)); //Cell farthest in +X,+Z
	Vector4F PosTopRight = pModTerrain->GetVertPos(PointtoVert(cell.coor.i + 1, cell.coor.j)); //Cell in the -X,+Z position
	Vector4F PosBottomLeft = pModTerrain->GetVertPos(PointtoVert(cell.coor.i, cell.coor.j + 1)); //Cell in the +X, -Z position
	Vector4F PosBottomRight = pModTerrain->GetVertPos(PointtoVert(cell.coor.i + 1, cell.coor.j + 1)); // Cell in the farthest -X, -Z position

	float height;

	//Distance between input position and BottomRight (-X,-Z) position
	Vector4F v2 = pos - PosBottomRight;

	if (v2[x] > v2[z]) {

		float beta = v2[x] * invCellWidth; //invCellWidth is the inverse of the cell width (1/cellWidth) which is calculated once on create for speed.
		float gamma = v2[z] * invCellWidth;

		height = PosBottomRight[y] + (beta * (PosBottomLeft[y] - PosBottomRight[y])) + (gamma * (PosTopLeft[y] - PosBottomLeft[y]));
	}
	else {

		float beta = v2[z] * invCellWidth;
		float gamma = v2[x] * invCellWidth;

		height = PosBottomRight[y] + (beta * (PosTopRight[y] - PosBottomRight[y])) + (gamma * (PosTopLeft[y] - PosTopRight[y]));
	}

	return height;
}


//Below are private Helper functions for user facing methods

int TerrainModel::TexelIndex(int i, int j) const {

	return pixel_width*(side * j + i);

}

int TerrainModel::PointtoVert(int i, int j) const {
	return i * side + j;

}

Vector4F TerrainModel::getTriNorm(const Vector4F& a, const Vector4F& b, const Vector4F& c) {

	
	return((a - b).Cross(a - c));
	
}

int TerrainModel::PosToCellNum(const Vector4F& pos) const
{
	float i = pos.X();

	i -= length * .5f;

	i = -i * invCellWidth;
	
	Math::ClampFloat(i, static_cast<float>(side - 2), 0);

	float j = pos.Z();

	j -= length * .5f;

	j = -j * invCellWidth;

	Math::ClampFloat(j, static_cast<float>(side - 2), 0);

	return PointtoVert(static_cast<int>(i), static_cast<int>(j));
}

TerrainCell& TerrainModel::PosToCell(const Vector4F& pos) {
	return CollisionAABBCollection[PosToCellNum(pos)];
}

TerrainCell& TerrainModel::CoorToCell(const TerrainCoordinates& coor) {
	return CollisionAABBCollection[PointtoVert(coor.i, coor.j)];
}

void TerrainModel::ReadFile(LPCWSTR filename)
{
	std::fstream hFile(filename, std::ios::in | std::ios::binary);
	if (!hFile.is_open()) { throw std::invalid_argument("File Not Found."); }

	std::uint8_t Header[18] = { 0 };
	std::vector<std::uint8_t> ImageData;
	static std::uint8_t DeCompressed[12] = { 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	static std::uint8_t IsCompressed[12] = { 0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	hFile.read(reinterpret_cast<char*>(&Header), sizeof(Header));

	if (!std::memcmp(DeCompressed, &Header, sizeof(DeCompressed)))
	{
		BitsPerPixel = Header[16];
		width = Header[13] * 256 + Header[12];
		height = Header[15] * 256 + Header[14];
		size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

		if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
		{
			hFile.close();
			throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
		}

		ImageData.resize(size);
		ImageCompressed = false;
		hFile.read(reinterpret_cast<char*>(ImageData.data()), size);
	}
	else if (!std::memcmp(IsCompressed, &Header, sizeof(IsCompressed)))
	{
		BitsPerPixel = Header[16];
		width = Header[13] * 256 + Header[12];
		height = Header[15] * 256 + Header[14];
		size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

		if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
		{
			hFile.close();
			throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
		}

		PixelInfo Pixel = { 0 };
		int CurrentByte = 0;
		std::size_t CurrentPixel = 0;
		ImageCompressed = true;
		std::uint8_t ChunkHeader = { 0 };
		int BytesPerPixel = (BitsPerPixel / 8);
		ImageData.resize(width * height * sizeof(PixelInfo));

		do
		{
			hFile.read(reinterpret_cast<char*>(&ChunkHeader), sizeof(ChunkHeader));

			if (ChunkHeader < 128)
			{
				++ChunkHeader;
				for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
			else
			{
				ChunkHeader -= 127;
				hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

				for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
		} while (CurrentPixel < static_cast<unsigned int>(width * height));
	}
	else
	{
		hFile.close();
		throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit TGA File.");
	}

	hFile.close();
	this->pixels = ImageData;
}

TerrainCell TerrainModel::PointToCell(const int&i, const int& j) {
	return CollisionAABBCollection[PointtoVert(i,j)];
}

Model* TerrainModel::GetModel() {
	return pModTerrain;
}
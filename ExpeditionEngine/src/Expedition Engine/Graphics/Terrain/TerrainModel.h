#ifndef TerrainModel_h
#define TerrainModel_h

#include "../../Math/Base/Align16.h"
#include <d3d12.h>
#include <vector>

class Model;
class Vector4F;
struct TerrainCell;
struct TerrainCoordinates;

class TerrainModel : public Align16
{
	friend class TerrainModelAttorney;
private:
	Model* pModTerrain;

	TerrainCell* CollisionAABBCollection;

	size_t side;
	const size_t pixel_width = 4;
	float length;
	float cellWidth;
	float invCellWidth;

	//Helper functions for frequently repeated math
	int TexelIndex(int i, int j) const;
	int PointtoVert(int i, int j) const;
	Vector4F getTriNorm(const Vector4F& a, const Vector4F& b, const Vector4F& c);
	int PosToCellNum(const Vector4F& pos) const;

	TerrainCell PointToCell(const int& i, const int&j);
	TerrainCell& PosToCell(const Vector4F& pos);
	TerrainCell& CoorToCell(const TerrainCoordinates& pos);

	std::vector<std::uint8_t> pixels;
	int width;
	int height;
	int size;
	int BitsPerPixel;
	bool ImageCompressed;
	void ReadFile(LPCWSTR filename);

public:

	Model* GetModel();
	
	//returns the barycentrifyed Normal on the terrain to create smooth normals across the terrain
	Vector4F BarycentrifyNormal(const Vector4F& pos);

	//returns the barycentrifyed height on the terrain to create smooth normals across the terrain
	float BarycentrifyHeight(const Vector4F& pos) const;
	
	float GetLength() { return length; };

	TerrainModel(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, ID3D12GraphicsCommandList4* cmdList);
	~TerrainModel();
	TerrainModel(TerrainModel&&) = delete;
	TerrainModel(const TerrainModel&) = delete;
	TerrainModel& operator = (TerrainModel&&) = delete;
	TerrainModel& operator = (const TerrainModel&) = delete;

};



#endif TerrainModel_h
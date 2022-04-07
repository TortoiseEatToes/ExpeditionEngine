#ifndef MODEL_H
#define MODEL_H

#include <d3d12.h>
#include "../../Math/Vector/Vector4F.h"

class MeshSeparator;

struct StandardVertex : public Align16
{
	Vector4F Pos;
	float u;
	float v;
	Vector4F normal;
	Vector4F Color;
	int meshNum;		// new property

	void set(float _x, float _y, float _z,
		float _u = 0, float _v = 0,
		float _nx = 0, float _ny = 0, float _nz = 0,
		float _r = 1, float _g = 1, float _b = 1, int num = 0)
	{
		Pos = Vector4F(_x, _y, _z, 1);
		u = _u;
		v = _v;
		normal = Vector4F(_nx, _ny, _nz, 0);
		Color = Vector4F(_r, _g, _b);
		meshNum = num;
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vector4F& c, int num = 0)
	{
		Pos = Vector4F(_x, _y, _z, 1);
		u = _u;
		v = _v;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vector4F& n, const Vector4F& c, int num = 0)
	{
		Pos = Vector4F(_x, _y, _z, 1);
		u = _u;
		v = _v;
		normal = n;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, const Vector4F& c, int num = 0)
	{
		Pos = Vector4F(_x, _y, _z, 1);
		u = 0;
		v = 0;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, const Vector4F& n, const Vector4F& c, int num = 0)
	{
		Pos = Vector4F(_x, _y, _z, 1);
		u = 0;
		v = 0;
		normal = n;
		Color = c;
		meshNum = num;
	}

	void set(const Vector4F& p, const Vector4F& c)
	{
		Pos = p;
		Color = c;
	}
};

struct TriangleByIndex
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;

	void set(int _v0, int _v1, int _v2)
	{
		v0 = static_cast<unsigned int>(_v0);
		v1 = static_cast<unsigned int>(_v1);
		v2 = static_cast<unsigned int>(_v2);
	}
};

class Model : public Align16
{
protected:
	// Model information
	TriangleByIndex * pTriList;
	StandardVertex* pStdVerts;
	Vector4F center;
	Vector4F AABBMax;
	Vector4F AABBMin;
	int numVerts;
	int numTris;
	float radius;

	MeshSeparator* meshes;

	ID3D12Resource* VertexBufferGPU = nullptr;
	ID3D12Resource* VertexBufferUploader = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vbv[1];

	ID3D12Resource* IndexBufferGPU = nullptr;
	ID3D12Resource* IndexBufferUploader = nullptr;
	D3D12_INDEX_BUFFER_VIEW ibv[1];

	void privLoadDataToGPU(ID3D12GraphicsCommandList4* cmdList);
	void privLoadDataFromFile(const char * _modelName, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& ptlist, int& ntri);
	ID3D12Resource* CreateDefaultBuffer(const void* initData, UINT64 bytesize, ID3D12GraphicsCommandList4* cmdList, ID3D12Resource*& uploadBuffer);

public:
	Model(const Model&) = delete;				// Copy constructor
	Model(Model&&) = delete;                    // Move constructor
	Model& operator=(const Model&) & = delete;  // Copy assignment operator
	Model& operator=(Model&&) & = delete;       // Move assignment operator

	enum PreMadeModels {
		UnitBox,
		UnitBoxSixFaceTexture,
		UnitBoxRepTexture,
		UnitPyramid,
		UnitSphere,
	};

	Model() {};
	Model(StandardVertex* pVerts, int nverts, TriangleByIndex* ptlist, int ntri, ID3D12GraphicsCommandList4* cmdList);
	Model(PreMadeModels pm, ID3D12GraphicsCommandList4* cmdList);

	Model(const char * const _modelName, ID3D12GraphicsCommandList4* cmdList);

	virtual ~Model();

	void SendToCmdList(ID3D12GraphicsCommandList4* cmdList);
	void Render(ID3D12GraphicsCommandList4* cmdList, int numOfInstances);
	void RenderMesh(ID3D12GraphicsCommandList4* cmdList, int meshnum, int numberOfInstances);

	// Get access
	int GetMeshCount();
	bool ValidMeshNum(int i);

	StandardVertex* GetVertList() {return pStdVerts;}
	StandardVertex GetVert(int i) {return pStdVerts[i];}
	int GetVertNum() {return numVerts;}
	Vector4F GetCenter() { return center; }
	float GetRadius() { return radius; }
	Vector4F GetAABBMax() { return AABBMax; }
	Vector4F GetAABBMin() { return AABBMin; }
	Vector4F GetVertPos(int i) { return pStdVerts[i].Pos; }
};



#endif
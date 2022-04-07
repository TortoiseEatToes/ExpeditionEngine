#include <assert.h>
#include "Model.h"
#include "ModelTools.h"
#include "../../DX12App/d3dUtil_12.h"
#include "MeshSeparator.h"
#include "../../Math/Vector/Vector4F.h"
#include "../AzulFileHdr.h"

#include "../../../Expedition Resources/EngineSettings.h"
#include "../../DX12App/DXApp/DXApp_12.h"
#include "../../DX12App/d3dx12.h"

Model::Model(StandardVertex *pVerts, int nverts, TriangleByIndex *ptlist, int ntri, ID3D12GraphicsCommandList4* cmdList)
{
	assert(nverts > 0);
	assert(ntri > 0);

	center = Vector4F(0,0,0,1);
	radius = 0;

	//mDevice = DXAppAttorney::GetControls::GetDevice();

	// Copy Data
	numVerts = nverts;
	pStdVerts = new StandardVertex[numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		pStdVerts[i] = pVerts[i];
	}
	numTris = ntri;
	pTriList = new TriangleByIndex[numTris];
	for (int i = 0; i < numTris; i++)
	{
		pTriList[i] = ptlist[i];
	}

	privLoadDataToGPU(cmdList);
}

Model::Model(const char * const _modelName, ID3D12GraphicsCommandList4* cmdList)
{
	//mDevice = DXAppAttorney::GetControls::GetDevice();
	pStdVerts = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;

	privLoadDataFromFile(_modelName, pStdVerts, numVerts, pTriList, numTris);
	privLoadDataToGPU(cmdList);
}

Model::Model(Model::PreMadeModels pm, ID3D12GraphicsCommandList4* cmdList)
{
	//mDevice = DXAppAttorney::GetControls::GetDevice();
	pStdVerts = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;
	center = Vector4F(0, 0, 0,1);
	radius = .5;

	switch (pm)
	{
	case UnitBox:
		ModelTools::CreateUnitBox(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitBoxSixFaceTexture:
		ModelTools::CreateUnitBoxSixFaceTexture(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitPyramid:
		ModelTools::CreateUnitPyramid(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitSphere:
		ModelTools::CreateUnitSphere(12, 12, pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitBoxRepTexture:
		ModelTools::CreateUnitBoxRepTexture(pStdVerts, numVerts, pTriList, numTris);
		break;
	default:
		assert(false && "Invalid option");
	}

	privLoadDataToGPU(cmdList);
}

Model::~Model()
{
	delete[] pTriList;
	delete[] pStdVerts;
	delete meshes;

	ReleaseAndDeleteCOMobject(VertexBufferGPU);
	ReleaseAndDeleteCOMobject(VertexBufferUploader);
	ReleaseAndDeleteCOMobject(IndexBufferGPU);
	ReleaseAndDeleteCOMobject(IndexBufferUploader);
}

void Model::privLoadDataFromFile(const char * _modelName, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& ptlist, int& ntri)
{
	// Read from file
	//FileHandle fh;
	//FileError  ferror;
	//
	//
	//
	//ferror = File::open(fh, _modelName, FILE_READ);
	//assert(ferror == FILE_SUCCESS);

	HANDLE fh;
	DWORD ferror;
	DWORD flocation;

	DWORD totalBytesRead = 0;
	
	// Open the file
	fh = CreateFile(
		_modelName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	
	assert(INVALID_HANDLE_VALUE != fh);
	
	ferror = SetFilePointer(fh, 0, NULL, FILE_BEGIN);
	
	assert(0 == ferror);

	// GEt the file format for the data
	AzulFileHdr  azulFileHdr;

	// **** Overly complicated detour Part 1:  The vertex data in the file is packed efficiently
	// whereas our StandardVertex is not. Something I shall fix form the start next time.
	// For time time: we will read in the data into a temp array and then manually copy the data into
	// the StandardVertex array. 

	struct VertexStride_VUN
	{
		float x;    // Vert - V
		float y;
		float z;

		float u;    // UV tex coor - U
		float v;

		float txt;	// texture trickery 

		float nx;   // Norm verts - N
		float ny;
		float nz;

		float r;
		float g;
		float b;

		void set(float _x, float _y, float _z,
			float _u, float _v,
			float _nx, float _ny, float _nz,
			float _txt = 0,
			float _r = 1, float _g = 1, float _b = 1)
		{
			x = _x;
			y = _y;
			z = _z;
			u = _u;
			v = _v;
			nx = _nx;
			ny = _ny;
			nz = _nz;

			txt = _txt;
			r = _r;
			g = _g;
			b = _b;
		}

	};

	// ******************


	// Read the header
	//ferror = File::read(fh, &azulFileHdr, sizeof(AzulFileHdr));
	//assert(ferror == FILE_SUCCESS);
	//
	ferror = ReadFile(fh, &azulFileHdr, sizeof(AzulFileHdr), &flocation, NULL); //Get file type
	assert(0 != ferror);

	totalBytesRead += flocation;

	// create the vertex buffer
	nverts = azulFileHdr.numVerts;
	VertexStride_VUN* pTmpVerts = new VertexStride_VUN[nverts];

	// load the verts
	// seek to the location
	//ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.vertBufferOffset);
	//assert(ferror == FILE_SUCCESS);
	//
	//// read it
	//ferror = File::read(fh, pTmpVerts, nverts * sizeof(VertexStride_VUN));
	//assert(ferror == FILE_SUCCESS);

	void* pTempBuff = new char[azulFileHdr.vertBufferOffset - totalBytesRead];

	ferror = ReadFile(fh, pTempBuff, azulFileHdr.vertBufferOffset - totalBytesRead, &flocation, NULL); //Get file type
	assert(0 != ferror);
	
	totalBytesRead += flocation;
	delete pTempBuff;

	ferror = ReadFile(fh, pTmpVerts, nverts * sizeof(VertexStride_VUN), &flocation, NULL); //Get file type
	assert(0 != ferror);
	totalBytesRead += flocation;

	// create the triLists buffer
	ntri = azulFileHdr.numTriangles;
	ptlist = new TriangleByIndex[ntri];

	//set center and radius
	center = azulFileHdr.center;
	radius = azulFileHdr.radius;

	//set Max/MinAABB
	AABBMax = azulFileHdr.maxPointAABB;
	AABBMin = azulFileHdr.minPointAABB;

	// load the triList
	// seek to the location

	pTempBuff = new char[azulFileHdr.triangleListBufferOffset - totalBytesRead];

	ferror = ReadFile(fh, pTempBuff, azulFileHdr.triangleListBufferOffset - totalBytesRead, &flocation, NULL); //Get file type
	totalBytesRead += flocation;
	delete pTempBuff;

	assert(0 != ferror);




	//ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.triangleListBufferOffset);
	//assert(ferror == FILE_SUCCESS);

	// read it
	ferror = ReadFile(fh, ptlist, ntri * sizeof(TriangleByIndex), &flocation, NULL); //Get file type
	totalBytesRead += flocation;
	assert(0 != ferror);
	//ferror = File::read(fh, ptlist, ntri * sizeof(TriangleByIndex));
	//assert(ferror == FILE_SUCCESS);

	// close
	ferror = CloseHandle(fh);
	assert(0 != ferror);

	//ferror = File::close(fh);
	//assert(ferror == FILE_SUCCESS);

	// **** Overly complicated detour Part 2: now we copy the vertex data into our StandardVertex
	pVerts = new StandardVertex[nverts];
	StandardVertex* v;
	VertexStride_VUN* tmp;
	for (int i = 0; i < nverts; i++)
	{
		tmp = &(pTmpVerts[i]);
		v = &(pVerts[i]);
		v->set(tmp->x, tmp->y, tmp->z, tmp->u, tmp->v, tmp->nx, tmp->ny, tmp->nz, tmp->r, tmp->g, tmp->b, (int)tmp->txt);
	}

	delete[] pTmpVerts;

	// *************************


}

void  Model::privLoadDataToGPU(ID3D12GraphicsCommandList4* cmdList)
{
	// Extract mesh information
	meshes = new MeshSeparator(pStdVerts, numVerts, pTriList, numTris);

	VertexBufferGPU = CreateDefaultBuffer(pStdVerts, numVerts * sizeof(StandardVertex), cmdList, VertexBufferUploader);

	vbv[0].BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
	vbv[0].StrideInBytes = sizeof(StandardVertex);
	vbv[0].SizeInBytes = numVerts * sizeof(StandardVertex);

	IndexBufferGPU = CreateDefaultBuffer(pTriList, numTris * sizeof(TriangleByIndex), cmdList, IndexBufferUploader);

	ibv[0].BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
	ibv[0].SizeInBytes = numTris * sizeof(TriangleByIndex);
	ibv[0].Format = DXGI_FORMAT_R32_UINT;
}

bool Model::ValidMeshNum(int meshnum)
{
	return (meshnum >= 0) && (meshnum < GetMeshCount());
}

int Model::GetMeshCount()
{
	return meshes->GetMeshCount();
}


void Model::SendToCmdList(ID3D12GraphicsCommandList4* cmdList)
{
	cmdList->IASetIndexBuffer(ibv);
	cmdList->IASetVertexBuffers(0, 1, vbv);
}

void Model::Render(ID3D12GraphicsCommandList4* cmdList, int numOfInstances)
{
	cmdList->DrawIndexedInstanced(static_cast<UINT>(numTris * 3), numOfInstances, 0, 0, 0);
}

void Model::RenderMesh(ID3D12GraphicsCommandList4* cmdList, int meshnum, int numberOfInstances)
{
	assert(ValidMeshNum(meshnum));

	int tricount, trioffset;
	meshes->GetMeshTriCountAndOffset(meshnum, tricount, trioffset);

	cmdList->DrawIndexedInstanced(static_cast<UINT>(tricount * 3), numberOfInstances, static_cast<UINT>(trioffset * 3), 0, 0);
}

ID3D12Resource* Model::CreateDefaultBuffer(const void* initData, UINT64 bytesize, ID3D12GraphicsCommandList4* cmdList, ID3D12Resource*& uploadBuffer)
{
	ID3D12Resource* defaultBuffer = nullptr;

	ID3D12Device5* device = DXApp_12::GetDevice();

	// This is the GPU side buffer
	HRESULT hr = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(bytesize), D3D12_RESOURCE_STATE_COMMON,
		nullptr, IID_PPV_ARGS(&defaultBuffer));
	assert(hr == S_OK);

	//To upload data to the gpu, we need an upload buffer
	hr = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(bytesize), D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&uploadBuffer));
	assert(hr == S_OK);

	// Data description
	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = static_cast<LONG_PTR>(bytesize);
	subResourceData.SlicePitch = subResourceData.RowPitch;

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));

	//helper function that copies CPU data into upload heap then uses ID3D12GraphicsCommandList4::CopySubresourceRegion
	// to copy upload heap data to defaultBuffer
	UpdateSubresources<1>(cmdList, defaultBuffer, uploadBuffer, 0, 0, 1, &subResourceData);

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));

	return defaultBuffer;
}
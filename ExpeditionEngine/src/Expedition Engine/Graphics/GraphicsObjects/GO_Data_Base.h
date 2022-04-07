#pragma once

#include "../../Containers/PooledResourceIterator.h"

#include <d3d12.h>

class GraphicsResourcesManager;

class Model;
struct Data_PerObject;

class TerrainModel;

class Matrix4FDoubleBuffer;
class PointerDoubleBuffer;
class Material;


class GO_Data_Base
{
	friend class GO_Data_BaseAttorney;
private:
	friend class GO_Data_TextureLightAttorney;
	friend class GO_Data_TextureAttorney;
	friend class GO_Data_ColorLightAttorney;
	friend class GO_Data_ColorAttorney;

	///<summary> Render the data on this object </summary>
	void PrepareToRender(ID3D12GraphicsCommandList4* cmdList);
	void Render_12(ID3D12GraphicsCommandList4* cmdList);

	///<summary> Sanatizes pooled GraphicsObjects </summary>
	void Sanitize_12(GraphicsResourcesManager* pGraphicsResourcesManager);

	void Initialize_12(GraphicsResourcesManager* pGraphicsResourcesManager, TerrainModel* mod);
	void Initialize_12(GraphicsResourcesManager* pGraphicsResourcesManager, Model* mod, int numberOfInsts);

public:
	Model* pModel;
	TerrainModel* terrainModel = nullptr;

	PooledResourceIterator<Matrix4FDoubleBuffer>* pWorld;
	Data_PerObject* pObjectData;
	PooledResourceIterator<PointerDoubleBuffer>** MeshTextures;

	Material*** pMeshMaterials;

	int meshCount;
	int numberOfInstances = -1;
	int* uploadBufferOffset;
};


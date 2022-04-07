#include "GO_Data_Base.h"

#include "../Graphics Resources/GraphicsResourcesManager.h"

#include "../Terrain/TerrainModelAttorney.h"
#include "../../DX12App/d3dUtil_12.h"

#include "../Model/Model.h"

#include "../../DX12App/DXApp/DXApp_12.h"
#include "../../DX12App/FrameResources/FrameResourceInstanced.h"
#include "../Model/Texture.h"
#include "../Model/Managers/TextureManager.h"
#include "../../../Expedition Resources/TextureSettings.h"

#include <assert.h>

void GO_Data_Base::PrepareToRender(ID3D12GraphicsCommandList4* cmdList)
{
	for (int i = 0; i < numberOfInstances; ++i)
	{
		pObjectData[i].World = pWorld[i].GetCurrentObject().GetDraw();
		pObjectData[i].WorldInv = pObjectData[i].World.InverseCopy();
	}

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		for (int j = 0; j < numberOfInstances; j++)
		{
			pObjectData[j].Mat.Ambient = pMeshMaterials[i][j]->Ambient().GetDraw();
			pObjectData[j].Mat.Specular = pMeshMaterials[i][j]->Specular().GetDraw();
			pObjectData[j].Mat.Diffuse = pMeshMaterials[i][j]->Diffuse().GetDraw();

			pObjectData[j].textureName = MeshTextures[i][j].GetCurrentObject().GetDrawTexture()->getName();
		}

		DXApp_12::GetFrameResourceInstanced()->SendObjectDataToUploadHeap(*pObjectData, uploadBufferOffset[i], numberOfInstances);
	}
}

void GO_Data_Base::Render_12(ID3D12GraphicsCommandList4* cmdList)
{
	pModel->SendToCmdList(cmdList);

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		DXApp_12::GetFrameResourceInstanced()->SendObjectUploadToDefault(cmdList, uploadBufferOffset[i], numberOfInstances);

		pModel->RenderMesh(cmdList, i, numberOfInstances);
	}
}

void GO_Data_Base::Sanitize_12(GraphicsResourcesManager* pGraphicsResourcesManager)
{
	for (int i = 0; i < numberOfInstances; i++)
	{
		pGraphicsResourcesManager->DeregisterFromSynchronization(pWorld[i]);
		pGraphicsResourcesManager->ReleaseDoubleBuffer(pWorld[i]);
	}

	delete[] pWorld;
	pWorld = nullptr;

	for (int i = 0; i < meshCount; i++) {
		for (int j = 0; j < numberOfInstances; j++)
		{
			pGraphicsResourcesManager->DeregisterFromSynchronization(pMeshMaterials[i][j]);
			pGraphicsResourcesManager->ReleaseMaterial(pMeshMaterials[i][j]);

			pGraphicsResourcesManager->DeregisterFromSynchronization(MeshTextures[i][j]);
			pGraphicsResourcesManager->ReleasePointer(MeshTextures[i][j]);
		}

		delete[] pMeshMaterials[i];
		pMeshMaterials[i] = nullptr;

		delete[] MeshTextures[i];
		MeshTextures[i] = nullptr;
	}

	delete[] pObjectData;
	pObjectData = nullptr;

	delete[] pMeshMaterials;
	pMeshMaterials = nullptr;

	delete[] MeshTextures;
	MeshTextures = nullptr;

	delete[] uploadBufferOffset;
	uploadBufferOffset = nullptr;
}

void GO_Data_Base::Initialize_12(GraphicsResourcesManager* pGraphicsResourcesManager, Model* mod, int numberOfInsts)
{
	numberOfInstances = numberOfInsts;

	pModel = mod;
	pWorld = new PooledResourceIterator<Matrix4FDoubleBuffer>[numberOfInstances];

	for (int i = 0; i < numberOfInstances; i++)
	{
		pGraphicsResourcesManager->AcquireDoubleBuffer(pWorld[i]);
		pGraphicsResourcesManager->RegisterForSynchronization(pWorld[i]);

		pWorld[i].GetCurrentObject().Initialize(Matrix4F(IDENTITY));
	}

	meshCount = mod->GetMeshCount();

	uploadBufferOffset = new int[meshCount];

	Texture* nullTex = TextureManager::Get(TextureName::Default);

	pMeshMaterials = new Material * *[meshCount];
	MeshTextures = new PooledResourceIterator<PointerDoubleBuffer> * [meshCount];

	for (int i = 0; i < meshCount; i++) {
		pMeshMaterials[i] = new Material * [numberOfInstances];

		MeshTextures[i] = new PooledResourceIterator<PointerDoubleBuffer>[numberOfInstances];

		for (int j = 0; j < numberOfInstances; j++) {
			pGraphicsResourcesManager->AcquireMaterial(pMeshMaterials[i][j]);
			pMeshMaterials[i][j]->Initialize(Vector4F(.5, .5, .5, 1));
			pGraphicsResourcesManager->RegisterForSynchronization(pMeshMaterials[i][j]);

			pGraphicsResourcesManager->AcquirePointer(MeshTextures[i][j]);
			MeshTextures[i][j].GetCurrentObject().Initialize(nullTex);
			pGraphicsResourcesManager->RegisterForSynchronization(MeshTextures[i][j]);
		}

	}

	pObjectData = new Data_PerObject[numberOfInstances];
}

void GO_Data_Base::Initialize_12(GraphicsResourcesManager* pGraphicsResourcesManager, TerrainModel* pTerrainModel)
{
	numberOfInstances = 1;
	terrainModel = pTerrainModel;

	this->Initialize_12(pGraphicsResourcesManager, pTerrainModel->GetModel(), 1);
}
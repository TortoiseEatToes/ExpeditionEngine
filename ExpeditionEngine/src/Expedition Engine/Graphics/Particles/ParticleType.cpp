#include "ParticleType.h"

#include "../../DX12App/d3dUtil_12.h"
#include "../GraphicsObjects/GO_Data_GPUObjects.h"

#include "ParticleBurst.h"
#include "Particle_PooledResourceIterator.h"

#include "../Model/Model.h"

#include "../../DX12App/Shaders/ShaderManager_12.h"
#include "../../DX12App/Shaders/ShaderParticle_12.h"
#include "../../DX12App/Shaders/ShaderBase_12.h"
#include "../Model/Texture.h"

#include "../../GraphicsScene/GraphicsSceneManager.h"
#include "../../GraphicsScene/GraphicsScene.h"
#include "../../Camera/Camera.h"

#include "../../../Expedition Resources/EngineSettings.h"

#include "../../DX12App/DXApp/DXApp_12.h"
#include "../../DX12App/d3dx12.h"

#include <d3d12.h>
#include <assert.h>
#include <list>

void ParticleType::Instantiate(Model* pInitModel, Texture* pInitTexture, int initNumberOfParticles) 
{
	pModel = pInitModel;
	pTexture = pInitTexture;
	numberOfInstances = initNumberOfParticles;

	HRESULT hr = DXApp_12::GetDevice()->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(GO_DataGPU_Particle) * numberOfInstances), D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&g_UploadBuffer));
	assert(hr == S_OK);

}

void ParticleType::PushBack(PooledResourceIterator<ParticleBurst>& currentBurstIterator)
{
	activeParticleBursts.PushBack(currentBurstIterator);
}

void ParticleType::Remove(PooledResourceIterator<ParticleBurst>& currentBurstIterator)
{
	activeParticleBursts.Remove(currentBurstIterator);
}



void ParticleType::ComputeAndRenderDX12(PooledResourceIterator<ParticleBurst>& currentBurstIterator, Particle_PooledResourceIterator& currentParticleIterator, const float& timeStep, const Vector4F& cameraPosition)
{	

	assert(numberOfInstances > -1);

	//---------------------------------------------------
	//This Sorts particles back to front
	//---------------------------------------------------

	///*

	//std::list<Particle> vectorList;
	
	//Send all of the particle data to the GPU
	numberOfParticles = 0;
	activeParticleBursts.SetFront(currentBurstIterator);
	while (!currentBurstIterator.IsOutOfNodes())
	{
		currentBurstIterator.GetCurrentObject().ComputeAndRenderDX12Sorted(currentParticleIterator, timeStep, cameraPosition, priorityQueue);
		numberOfParticles += currentBurstIterator.GetCurrentObject().GetNumberOfParticles();
		++currentBurstIterator;
	}
	
	//vectorList.sort([](const Particle& a, const Particle& b) { return a.distFromCamSqr > b.distFromCamSqr; });
	
	
	g_UploadBuffer->Map(0, nullptr, &mappedResource_12);
	
	Particle* temp;

	while (priorityQueue.Size() > 0) {
		priorityQueue.Pop(temp);
		temp->RenderDX12(mappedResource_12);
		mappedResource_12 = (char*)mappedResource_12 + sizeof(GO_DataGPU_Particle);
	}
	
	g_UploadBuffer->Unmap(0, nullptr);
	//*/

	//----------------------------------------------------------

	//----------------------------------------------
	// No Sort
	//----------------------------------------------

	/*

	g_UploadBuffer->Map(0, nullptr, &mappedResource_12);
	
	//Send all of the particle data to the GPU
	numberOfParticles = 0;
	activeParticleBursts.SetFront(currentBurstIterator);
	while (!currentBurstIterator.IsOutOfNodes())
	{
		currentBurstIterator.GetCurrentObject().ComputeAndRenderDX12(currentParticleIterator, timeStep, cameraPosition, mappedResource_12);
		numberOfParticles += currentBurstIterator.GetCurrentObject().GetNumberOfParticles();
		++currentBurstIterator;
	}
	
	
	g_UploadBuffer->Unmap(0, nullptr);

	//*/

	//--------------------------------------------------------

	pModel->SendToCmdList(DXApp_12::GetParticleCommandList());
	static_cast<ShaderParticle_12*>(ShaderManager_12::Get(ShaderName::ParticleShader))->UpdateTexture(pTexture->getName());
	DXApp_12::GetFrameResourceInstanced()->SendParticleObjectDataToGPU(g_UploadBuffer, DXApp_12::GetParticleCommandList(), numberOfParticles);
	pModel->RenderMesh(DXApp_12::GetParticleCommandList(), 0, numberOfParticles);

}

void ParticleType::ReleaseAllResources(PooledResourceIterator<ParticleBurst>& currentBurstIterator, Particle_PooledResourceIterator& currentParticleIterator, Particle_PooledResourcePool& particlePool)
{
	while (activeParticleBursts.GetSize() > 0)
	{
		activeParticleBursts.PopFront(currentBurstIterator);
		currentBurstIterator.GetCurrentObject().ReleaseAllParticles(currentParticleIterator, particlePool);
	}
}

TextureName& ParticleType::GetTextureName()
{
	return pTexture->getName();
}

ParticleType::ParticleType() : priorityQueue(NumberOfParticles)
{
}

ParticleType::~ParticleType()
{
	ReleaseAndDeleteCOMobject(g_UploadBuffer);
}
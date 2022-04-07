#include "FrameResourceInstanced.h"
#include "../DXApp/DXApp_12.h"
#include "../d3dx12.h"
#include "../d3dUtil_12.h"
#include "../../Camera/CameraData.h"
#include "../../Graphics/Model/Managers/TextureManager.h"
#include "../../../Expedition Resources/EngineSettings.h"
#include "../../../Expedition Resources/LightSettings.h"

#include "../../Graphics/Graphics Resources/Material.h"

#include "../../../Expedition Resources/GraphicsResourcesSettings.h"

#include "../../GraphicsScene/GraphicsSceneManager.h"
#include "../Shadows/ShadowMap.h"

#include "../../../Expedition Resources/LayerSettings.h"

FrameResourceInstanced::FrameResourceInstanced()
{
	//get important values

	cbvDescSize = DXApp_12::GetCBVDescSize();

	ID3D12Device* device = DXApp_12::GetDevice();


	//------------------------------------
	// Shadow Stuff
	//------------------------------------

	//pShadowMap = new ShadowMap(DXApp_12::GetDevice(), 2048, 2048);
	//
	//shadowCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	//
	//shadowCamera->setOrthographic(0, 200, 0, 200, 1.0f, 1000.0f);
	//shadowCamera->setOrientAndPosition(Vector4F(0, 1, 0), Vector4F(0, 0, 0, 1), Vector4F(0, 100, 100, 1));
	//
	//shadowCamera->updateCamera();

	//------------------------------------

	//------------------------------------------------------
	// INSTANCING STUFF
	//------------------------------------------------------

	int instanceBufferSize = perFrameBuffSize + (perObjBuffSize * MaxGraphicsObjectInstances) + (perParticleBuffSize * NumberOfParticles) + (ShadowBuffSize * (NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene));
	int uploadBufferSize = perFrameBuffSize + (perObjBuffSize * MaxGraphicsObjectInstances * NumberOfGraphicsObjects) + (ShadowBuffSize * (NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene));

	// This is the GPU side buffer
	HRESULT hr = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(instanceBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&g_InstanceDefaultHeap));
	assert(hr == S_OK);

	g_InstanceDefaultHeap->SetName(L"Frame Resource Default");

	//To upload data to the gpu, we need an upload buffer
	hr = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&g_InstanceUploadHeap));
	assert(hr == S_OK);

	g_InstanceUploadHeap->SetName(L"Frame Resource Upload");


	//------------------------------------------------------
	// Create Desc Heap (Where pointers to data are stored)
	//------------------------------------------------------

	D3D12_DESCRIPTOR_HEAP_DESC cbv_srv_Heap_Desc = {};
	cbv_srv_Heap_Desc.NumDescriptors = numOfDescriptors + ((NumberOfDirectionalLightsPerScene+NumberOfSpotLightsPerScene) * 2) + NumberOfTextures;
	cbv_srv_Heap_Desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbv_srv_Heap_Desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbv_srv_Heap_Desc.NodeMask = 0;

	device->CreateDescriptorHeap(&cbv_srv_Heap_Desc, IID_PPV_ARGS(&g_CBV_SRV_DescHeap));

	//-----------------------------------------------------------
	// Fill in the Descriptor info that wont change
	//-----------------------------------------------------------

	//Create FRAME CBV 
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = g_InstanceDefaultHeap->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = perFrameBuffSize;

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle(g_CBV_SRV_DescHeap->GetCPUDescriptorHandleForHeapStart());

	device->CreateConstantBufferView(&cbvDesc, handle);

	for (int i = 0; i < NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene; i++) 
	{
		cbvDesc.BufferLocation = g_InstanceDefaultHeap->GetGPUVirtualAddress() + perFrameBuffSize + (ShadowBuffSize * i);
		cbvDesc.SizeInBytes = ShadowBuffSize;

		handle.Offset(1, cbvDescSize);

		device->CreateConstantBufferView(&cbvDesc, handle);
	}


	//Create instance buffer views
	int offset = 0;

	range_Frame.Begin = offset;
	offset += perFrameBuffSize;
	range_Frame.End = offset;

	range_Shadow.Begin = offset;
	offset += ShadowBuffSize * (NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene);
	range_Shadow.End = offset;

	instanceBufferViews[0].BufferLocation = g_InstanceDefaultHeap->GetGPUVirtualAddress() + offset;
	instanceBufferViews[0].StrideInBytes = perObjBuffSize;
	instanceBufferViews[0].SizeInBytes = (perObjBuffSize * MaxGraphicsObjectInstances);

	range_Object.Begin = offset;
	offset += perObjBuffSize * MaxGraphicsObjectInstances;
	range_Object.End = offset;

	instanceBufferViews[1].BufferLocation = g_InstanceDefaultHeap->GetGPUVirtualAddress() + offset;
	instanceBufferViews[1].StrideInBytes = perParticleBuffSize;
	instanceBufferViews[1].SizeInBytes = perParticleBuffSize * NumberOfParticles;

	range_Particle.Begin = offset;
	offset += perParticleBuffSize * NumberOfParticles;
	range_Particle.End = offset;

	//---------------------------------------------------
	// Create Command Objects
	//---------------------------------------------------

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_PreRenderCommandAllocator));
	assert(hr == S_OK);

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_PostRenderCommandAllocator));
	assert(hr == S_OK);

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_RenderCommandAllocator));
	assert(hr == S_OK);

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_ParticleCommandAllocator));
	assert(hr == S_OK);

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_ShadowCommandAllocator));
	assert(hr == S_OK);
}

FrameResourceInstanced::~FrameResourceInstanced()
{
	ReleaseAndDeleteCOMobject(g_CBV_SRV_DescHeap);
	ReleaseAndDeleteCOMobject(g_InstanceUploadHeap);

	ReleaseAndDeleteCOMobject(g_InstanceDefaultHeap);
	ReleaseAndDeleteCOMobject(g_PostRenderCommandAllocator);
	ReleaseAndDeleteCOMobject(g_PreRenderCommandAllocator);
	ReleaseAndDeleteCOMobject(g_RenderCommandAllocator);
	ReleaseAndDeleteCOMobject(g_ParticleCommandAllocator);
	ReleaseAndDeleteCOMobject(g_ShadowCommandAllocator);
}

void FrameResourceInstanced::UpdatePerFrameData(const CameraData& cameraData, ID3D12GraphicsCommandList4* cmdList)
{
	for (int i = 0; i < NumberOfDirectionalLightsPerScene && i < LightManager::MAX_DIRC_LIGHTS; i++) {
		frameBuffer.DirLight[i].Mat.Ambient = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetDirectionalLight(i).GetMaterial()->Ambient().GetDraw();
		frameBuffer.DirLight[i].Mat.Diffuse = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetDirectionalLight(i).GetMaterial()->Diffuse().GetDraw();
		frameBuffer.DirLight[i].Mat.Specular = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetDirectionalLight(i).GetMaterial()->Specular().GetDraw();
		frameBuffer.DirLight[i].Direction = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetDirectionalLight(i).GetDirection()->GetDraw();
	}

	for (int i = 0; i < NumberOfPointLightsPerScene && i < LightManager::MAX_POINT_LIGHTS; i++) {
		frameBuffer.PntLightList[i].Mat.Ambient = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetPointLight(i).GetMaterial()->Ambient().GetDraw();
		frameBuffer.PntLightList[i].Mat.Diffuse = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetPointLight(i).GetMaterial()->Diffuse().GetDraw();
		frameBuffer.PntLightList[i].Mat.Specular = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetPointLight(i).GetMaterial()->Specular().GetDraw();
		frameBuffer.PntLightList[i].Attenuation = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetPointLight(i).GetAttenuation()->GetDraw();
		frameBuffer.PntLightList[i].Position = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetPointLight(i).GetPosition()->GetDraw();

	}

	for (int i = 0; i < NumberOfSpotLightsPerScene && i < LightManager::MAX_SPOT_LIGHTS; i++) {
		frameBuffer.SptLightList[i].Mat.Ambient = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(i).GetMaterial()->Ambient().GetDraw();
		frameBuffer.SptLightList[i].Mat.Diffuse = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(i).GetMaterial()->Diffuse().GetDraw();
		frameBuffer.SptLightList[i].Mat.Specular = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(i).GetMaterial()->Specular().GetDraw();
		frameBuffer.SptLightList[i].Attenuation = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(i).GetAttenuation()->GetDraw();
		frameBuffer.SptLightList[i].Position = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(i).GetPosition()->GetDraw();
		frameBuffer.SptLightList[i].Direction = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(i).GetDirection()->GetDraw();
	}

	Vector4F eyepos;

	cameraData.GetPosition(eyepos);

	frameBuffer.EyePosWorld = eyepos;
	frameBuffer.View = cameraData.GetViewMatrix();
	frameBuffer.Projection = cameraData.GetProjMatrix();


	g_InstanceUploadHeap->Map(0, nullptr, &pMappedResource);

	memcpy(pMappedResource, &frameBuffer, perFrameBuffSize);

	g_InstanceUploadHeap->Unmap(0, nullptr);

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));

	cmdList->CopyBufferRegion(g_InstanceDefaultHeap, 0, g_InstanceUploadHeap, 0, perFrameBuffSize);

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
}

void FrameResourceInstanced::SendShadowDataToGPU(const Data_Shadow& shadow, ID3D12GraphicsCommandList4* cmdList, const int& offset)
{
	g_InstanceUploadHeap->Map(0, nullptr, &pMappedResource);

	pMappedResource = (char*)pMappedResource + perFrameBuffSize + (ShadowBuffSize * offset);
	memcpy(pMappedResource, &shadow, sizeof(Data_Shadow));

	g_InstanceUploadHeap->Unmap(0, nullptr);

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));

	cmdList->CopyBufferRegion(g_InstanceDefaultHeap, range_Shadow.Begin + (ShadowBuffSize * offset), g_InstanceUploadHeap, perFrameBuffSize + (ShadowBuffSize * offset), sizeof(Data_Shadow));

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
}

void FrameResourceInstanced::UpdateTextureDescriptors(CD3DX12_CPU_DESCRIPTOR_HANDLE handle)
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE Src = handle;

	CD3DX12_CPU_DESCRIPTOR_HANDLE Dst = CD3DX12_CPU_DESCRIPTOR_HANDLE(g_CBV_SRV_DescHeap->GetCPUDescriptorHandleForHeapStart(), numOfDescriptors + ((NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene)*2), cbvDescSize);

	DXApp_12::GetDevice()->CopyDescriptorsSimple(NumberOfTextures, Dst, Src, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void FrameResourceInstanced::UpdateShadowDescriptorsDirectional(const int& lightIndex)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle(g_CBV_SRV_DescHeap->GetCPUDescriptorHandleForHeapStart(), numOfDescriptors + NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene + lightIndex, cbvDescSize);

	DXApp_12::GetDevice()->CreateShaderResourceView(GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetDirectionalLight(lightIndex).GetShadow()->GetResource(), &srvDesc, handle);
 }

void FrameResourceInstanced::UpdateShadowDescriptorsSpotLight(const int& lightIndex)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle(g_CBV_SRV_DescHeap->GetCPUDescriptorHandleForHeapStart(), numOfDescriptors + NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene + lightIndex, cbvDescSize);

	DXApp_12::GetDevice()->CreateShaderResourceView(GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(lightIndex - NumberOfDirectionalLightsPerScene).GetShadow()->GetResource(), &srvDesc, handle);
}

//void FrameResourceInstanced::SendObjectDataToGPU(ID3D12Resource* buffer, ID3D12GraphicsCommandList4* cmdList, int NumberOfInstances, int StartingCopyInstance)
//{
//	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));
//
//	cmdList->CopyBufferRegion(g_InstanceDefaultHeap, range_Object.Begin, buffer, sizeof(Data_PerObject) * StartingCopyInstance, sizeof(Data_PerObject) * NumberOfInstances);
//
//	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
//}

void FrameResourceInstanced::SendObjectUploadToDefault(ID3D12GraphicsCommandList4* cmdList, int offset, int NumberOfInstances)
{

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));

	cmdList->CopyBufferRegion(g_InstanceDefaultHeap, range_Object.Begin, g_InstanceUploadHeap, offset, perObjBuffSize * NumberOfInstances);

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
}

void FrameResourceInstanced::SendObjectDataToUploadHeap(const Data_PerObject& buffer, int& offset,  int NumberOfInstances, int StartingCopyInstance)
{
	g_InstanceUploadHeap->Map(0, nullptr, &pMappedResource);

	offset = perFrameBuffSize + (ShadowBuffSize * (NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene)) + (currentUploadBuffer * (perObjBuffSize * MaxGraphicsObjectInstances)) + (StartingCopyInstance * perObjBuffSize);

	pMappedResource = (char*)pMappedResource + offset;

	memcpy(pMappedResource, &buffer, perObjBuffSize * NumberOfInstances);

	g_InstanceUploadHeap->Unmap(0, nullptr);

	currentUploadBuffer++;
	currentUploadBuffer = currentUploadBuffer % NumberOfGraphicsObjects;
}

void FrameResourceInstanced::SendParticleObjectDataToGPU(ID3D12Resource* buffer, ID3D12GraphicsCommandList4* cmdList, int NumberOfInstances, int StartingCopyInstance)
{
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));

	cmdList->CopyBufferRegion(g_InstanceDefaultHeap, range_Particle.Begin, buffer, perParticleBuffSize * StartingCopyInstance, perParticleBuffSize * NumberOfInstances);

	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_InstanceDefaultHeap, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
}



ID3D12DescriptorHeap* FrameResourceInstanced::GetCBV_SRVDescHeap()
{
	return g_CBV_SRV_DescHeap;
}

D3D12_GPU_DESCRIPTOR_HANDLE FrameResourceInstanced::GetGPUHandle_PerFrame()
{
	return CD3DX12_GPU_DESCRIPTOR_HANDLE(g_CBV_SRV_DescHeap->GetGPUDescriptorHandleForHeapStart());
}

D3D12_GPU_DESCRIPTOR_HANDLE FrameResourceInstanced::GetGPUHandle_ShadowCBV(const int& offset)
{
	return CD3DX12_GPU_DESCRIPTOR_HANDLE(g_CBV_SRV_DescHeap->GetGPUDescriptorHandleForHeapStart(), numOfDescriptors + offset, cbvDescSize);
}

D3D12_GPU_DESCRIPTOR_HANDLE FrameResourceInstanced::GetGPUHandle_ShadowSRV(const int& offset)
{
	return CD3DX12_GPU_DESCRIPTOR_HANDLE(g_CBV_SRV_DescHeap->GetGPUDescriptorHandleForHeapStart(), numOfDescriptors + NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene + offset, cbvDescSize);
}

D3D12_GPU_DESCRIPTOR_HANDLE FrameResourceInstanced::GetGPUHandle_TextureHeap()
{
	return CD3DX12_GPU_DESCRIPTOR_HANDLE(g_CBV_SRV_DescHeap->GetGPUDescriptorHandleForHeapStart(), numOfDescriptors + ((NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene) * 2), cbvDescSize);
}

const D3D12_VERTEX_BUFFER_VIEW& FrameResourceInstanced::GetVBV_Object()
{
	return instanceBufferViews[0];
}


const D3D12_VERTEX_BUFFER_VIEW& FrameResourceInstanced::GetVBV_Particle()
{
	return instanceBufferViews[1];
}

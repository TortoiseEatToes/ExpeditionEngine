#pragma once

#include "../../../Expedition Resources/TextureSettings.h"
#include "../Shaders/UploadStructs_12.h"
#include "../../Graphics/GraphicsObjects/GO_Data_GPUObjects.h"
#include <d3d12.h>
#include "../d3dx12.h"

class Camera;
class ShadowMap;
class CameraData;

class FrameResourceInstanced : public Align16
{
private:

	ID3D12CommandAllocator* g_PreRenderCommandAllocator;
	ID3D12CommandAllocator* g_PostRenderCommandAllocator;
	ID3D12CommandAllocator* g_RenderCommandAllocator;
	ID3D12CommandAllocator* g_ParticleCommandAllocator;
	ID3D12CommandAllocator* g_ShadowCommandAllocator;

	ID3D12Resource* g_InstanceUploadHeap;
	ID3D12Resource* g_InstanceDefaultHeap;

	D3D12_VERTEX_BUFFER_VIEW instanceBufferViews[2];

	ID3D12DescriptorHeap* g_CBV_SRV_DescHeap;

	Data_PerFrame frameBuffer;

	D3D12_RANGE range_Frame;
	D3D12_RANGE range_Shadow;
	D3D12_RANGE range_Object;
	D3D12_RANGE range_Particle;

	void* pMappedResource;
	Data_Shadow shadowData;

	static const int perObjBuffSize = sizeof(Data_PerObject);
	static const int perObjBuffSizeAligned = ((sizeof(Data_PerObject) + 255) & ~255);
	static const int perParticleBuffSize = sizeof(GO_DataGPU_Particle);
	static const int perFrameBuffSize = ((sizeof(Data_PerFrame) + 255) & ~255);
	static const int ShadowBuffSize = ((sizeof(Data_Shadow) + 255) & ~255);

	static const int numOfDescriptors = 1;

	int currentUploadBuffer = 0;
	int cbvDescSize;

public:
	FrameResourceInstanced();
	FrameResourceInstanced(FrameResourceInstanced&&) = delete;
	FrameResourceInstanced(const FrameResourceInstanced&) = delete;
	const FrameResourceInstanced& operator = (FrameResourceInstanced&&) = delete;
	const FrameResourceInstanced& operator = (const FrameResourceInstanced&) = delete;
	~FrameResourceInstanced();

	void UpdatePerFrameData(const CameraData& cameraData, ID3D12GraphicsCommandList4* cmdList);
	void SendShadowDataToGPU(const Data_Shadow& shadow, ID3D12GraphicsCommandList4* cmdList, const int& offset);
	void UpdateTextureDescriptors(CD3DX12_CPU_DESCRIPTOR_HANDLE handle);
	void UpdateShadowDescriptorsSpotLight(const int& lightIndex);
	void UpdateShadowDescriptorsDirectional(const int& lightIndex);

	void SendObjectUploadToDefault(ID3D12GraphicsCommandList4* cmdList, int offset, int NumberOfInstances = 1);
	void SendObjectDataToUploadHeap(const Data_PerObject& buffer, int& offset, int NumberOfInstances = 1, int StartingCopyInstance = 0);
	void SendParticleObjectDataToGPU(ID3D12Resource* buffer, ID3D12GraphicsCommandList4* cmdList, int NumberOfInstances = 1, int StartingCopyInstance = 0);

	ID3D12DescriptorHeap* GetCBV_SRVDescHeap();

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle_PerFrame();
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle_ShadowCBV(const int& offset);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle_ShadowSRV(const int& offset);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle_TextureHeap();

	const D3D12_VERTEX_BUFFER_VIEW& GetVBV_Object();
	const D3D12_VERTEX_BUFFER_VIEW& GetVBV_Particle();

	ID3D12CommandAllocator* GetPreRenderCommandAllocator()
	{
		return g_PreRenderCommandAllocator;
	}

	ID3D12CommandAllocator* GetPostRenderCommandAllocator()
	{
		return g_PostRenderCommandAllocator;
	}

	ID3D12CommandAllocator* GetRenderCommandAllocator()
	{
		return g_RenderCommandAllocator;
	}

	ID3D12CommandAllocator* GetParticleCommandAllocator()
	{
		return g_ParticleCommandAllocator;
	}

	ID3D12CommandAllocator* GetShadowCommandAllocator()
	{
		return g_ShadowCommandAllocator;
	}

};



#include "DXApp_12.h"
#include "../d3dUtil_12.h"
#include <assert.h>
#include "../d3dx12.h"
#include <d3dcompiler.h>
#include "../Shaders/ShaderColor_12.h"
#include "../Shaders/ShaderColorLight_12.h"
#include "../Shaders/ShaderTexture_12.h"
#include "../FrameResources/FrameResourceInstanced.h"
#include "../../../Expedition Resources/EngineSettings.h"
#include "../../Graphics/Light/LightManager.h"
#include "../../Graphics/Graphics Resources/Material.h"
#include "../../Graphics/Model/Managers/ModelManagerAttorney.h"
#include "../../Graphics/Model/Managers/TextureManagerAttorney.h"
#include "../../Graphics/Terrain/TerrainObjectManager.h"
#include "../Shaders/ShaderManagerAttorney_12.h"

#include "../../GraphicsScene/GraphicsSceneManager.h"

#include "../Shadows/ShadowMap.h"

int DXApp_12::currentFrame = 0;

DXApp_12* DXApp_12::pInstance = nullptr;

DXApp_12::DXApp_12() 
{
}

void DXApp_12::privInitialize(HWND hWnd)
{
	RECT rect;

	GetClientRect(hWnd, &rect);

	ClientWindowWidth = static_cast<float>(rect.right - rect.left);
	ClientWindowHeight = static_cast<float>(rect.bottom - rect.top);

	MainWindow = hWnd;

#if defined(DEBUG) || defined (_DEBUG)
	EnableDebugLayer();
#endif

	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&g_DXGIFactory));

	assert(hr == S_OK);

	CreateDevice();
	CreateFence();
	CheckMSAAQuality();
	QueryDescriptors();
	CreateDescriptorHeaps();

	for (int i = 0; i < NumberOfFrames; i++) {
		frameResourceInst[i] = new FrameResourceInstanced();
	}

	frameResourceInst[currentFrame]->GetRenderCommandAllocator()->Reset();

	CreateCommandObjects();
	CreateSwapChain();
	CreateRenderTargetViews();
	SetViewPort();



	g_RenderCommandList->Reset(frameResourceInst[currentFrame]->GetRenderCommandAllocator(), nullptr);

	CreateDepthStencilView();
	InitializeEngineResources();

	g_RenderCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DXApp_12::privDoneUploadingResources()
{
	HRESULT hr = g_RenderCommandList->Close();
	assert(hr == S_OK);

	ID3D12CommandList* mCmdsList[] = { g_RenderCommandList};

	g_CommandQueue->ExecuteCommandLists(_countof(mCmdsList), mCmdsList);

	FlushCommandQueue();

}


void DXApp_12::privFinishRendering()
{
	HRESULT hr = frameResourceInst[currentFrame]->GetPostRenderCommandAllocator()->Reset();
	assert(hr == S_OK);

	hr = g_PostRenderCommandList->Reset(frameResourceInst[currentFrame]->GetPostRenderCommandAllocator(), nullptr);
	assert(hr == S_OK);

	//--------------------------------------------------------
	// STEP 4: Change back buffer to front buffer
	//--------------------------------------------------------

	g_PostRenderCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
		g_mSwapChainBuffer[CurrentBackBuffer],
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT
	));

	//----------------------------------------------
	// STEP 5: Close and execute command list
	//----------------------------------------------

	hr = g_PostRenderCommandList->Close();
	assert(hr == S_OK);

	hr = g_RenderCommandList->Close();
	assert(hr == S_OK);

	hr = g_ParticleCommandList->Close();
	assert(hr == S_OK);

	ID3D12CommandList* mCmdsList[] = { g_PreRenderCommandList, g_ShadowCommandList, g_RenderCommandList, g_ParticleCommandList, g_PostRenderCommandList};

	g_CommandQueue->ExecuteCommandLists(_countof(mCmdsList), mCmdsList);


}

void DXApp_12::privPrepareToRender()
{
	//---------------------------------------------
	// STEP 6: Wait for Command Queue to finish and swap the chain! Easy Peasy
	//---------------------------------------------

	FlushCommandQueue();

	HRESULT hr = g_SwapChain->Present(0, 0);

	assert(hr == S_OK);

	CurrentBackBuffer = (CurrentBackBuffer + 1) % SwapChainBufferCount;

	//-------------------------------------
	// STEP 1: RESET COMMANDS
	//-------------------------------------

	hr = frameResourceInst[currentFrame]->GetPreRenderCommandAllocator()->Reset();
	assert(hr == S_OK);

	hr = frameResourceInst[currentFrame]->GetRenderCommandAllocator()->Reset();
	assert(hr == S_OK);

	hr = frameResourceInst[currentFrame]->GetParticleCommandAllocator()->Reset();
	assert(hr == S_OK);

	hr = g_PreRenderCommandList->Reset(frameResourceInst[currentFrame]->GetPreRenderCommandAllocator(), nullptr);
	assert(hr == S_OK);

	hr = g_RenderCommandList->Reset(frameResourceInst[currentFrame]->GetRenderCommandAllocator(), nullptr);
	assert(hr == S_OK);

	hr = g_ParticleCommandList->Reset(frameResourceInst[currentFrame]->GetParticleCommandAllocator(), nullptr);
	assert(hr == S_OK);

	//-----------------------------------------
	// STEP 2: CHANGE PRESENT BUFFER (FRONT BUFFER) TO RENDER TARGET (BACK BUFFER)
	// AND CLEAR DEPTH STENCIL AND RENDER TARGET
	//-----------------------------------------


	g_PreRenderCommandList->ResourceBarrier(
		1, &CD3DX12_RESOURCE_BARRIER::Transition(
			g_mSwapChainBuffer[CurrentBackBuffer],
			D3D12_RESOURCE_STATE_PRESENT, //state before
			D3D12_RESOURCE_STATE_RENDER_TARGET) //state after
	);

	g_PreRenderCommandList->ClearRenderTargetView(
		CurrentBackBufferView(),
		BackgroundColor, 0, nullptr);

	g_PreRenderCommandList->ClearDepthStencilView(
		DepthStencilView(0), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.0f, 0, 0, nullptr);

	hr = g_PreRenderCommandList->Close();
	assert(hr == S_OK);

	//-----------------------------------------------------------
	// STEP 3: User Draws
	//-----------------------------------------------------------

	g_RenderCommandList->RSSetViewports(1, &vp);
	g_RenderCommandList->RSSetScissorRects(1, &scissorRect);

	g_ParticleCommandList->RSSetViewports(1, &vp);
	g_ParticleCommandList->RSSetScissorRects(1, &scissorRect);

	g_RenderCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView(0));
	g_ParticleCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView(0));

	descHeaps[0] = frameResourceInst[currentFrame]->GetCBV_SRVDescHeap();

	g_RenderCommandList->SetDescriptorHeaps(2, descHeaps);
	g_ParticleCommandList->SetDescriptorHeaps(2, descHeaps);

	g_RenderCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_ParticleCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DXApp_12::privUpdateTextureDescriptors(CD3DX12_CPU_DESCRIPTOR_HANDLE handle)
{
	for (int i = 0; i < NumberOfFrames; i++) 
	{
		frameResourceInst[i]->UpdateTextureDescriptors(handle);
	}
}
	
void DXApp_12::privPrepareToRenderShadows()
{
	HRESULT hr = frameResourceInst[currentFrame]->GetShadowCommandAllocator()->Reset();
	assert(hr == S_OK);

	hr = g_ShadowCommandList->Reset(frameResourceInst[currentFrame]->GetShadowCommandAllocator(), nullptr);
	assert(hr == S_OK);

	g_ShadowCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	g_ShadowCommandList->SetGraphicsRootSignature(g_RootSig_Shadow);
	
	descHeaps[0] = frameResourceInst[currentFrame]->GetCBV_SRVDescHeap();
	
	g_ShadowCommandList->SetDescriptorHeaps(2, descHeaps);

	ShaderManager_12::Get(ShaderName::Shadow)->PrepareToRender(g_ShadowCommandList);
}

void DXApp_12::privPrepareShadow(Shadow* pShadow)
{
	int offset = 1 + pShadow->offset;

	g_ShadowCommandList->RSSetViewports(1, pShadow->GetViewPort());
	g_ShadowCommandList->RSSetScissorRects(1, pShadow->GetRect());

	g_ShadowCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pShadow->GetResource(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	g_ShadowCommandList->ClearDepthStencilView(
		DepthStencilView(offset), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.0f, 0, 0, nullptr);

	g_ShadowCommandList->OMSetRenderTargets(0, nullptr, false, &DepthStencilView(offset));

	g_ShadowCommandList->SetGraphicsRootDescriptorTable(0, DXApp_12::GetFrameResourceInstanced()->GetGPUHandle_ShadowCBV(pShadow->offset));
}

void DXApp_12::privCloseShadow(Shadow* pShadow)
{
	g_ShadowCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pShadow->GetResource(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ));

}

void DXApp_12::privFinishRenderingShadows()
{
	HRESULT hr = g_ShadowCommandList->Close();
	assert(hr == S_OK);
}

void DXApp_12::privUpdateShadowDescriptorsDirectional(const int& offset)
{
	for (int i = 0; i < NumberOfFrames; i++)
	{
		frameResourceInst[i]->UpdateShadowDescriptorsDirectional(offset);
	}

	D3D12_DEPTH_STENCIL_VIEW_DESC depthstencilviewdesc = {};
	depthstencilviewdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthstencilviewdesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthstencilviewdesc.Texture2D.MipSlice = 0;


	g_Device->CreateDepthStencilView(GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetDirectionalLight(offset).GetShadow()->GetResource(), &depthstencilviewdesc,
		DepthStencilView(1 + offset));
}

void DXApp_12::privUpdateShadowDescriptorsSpotLight(const int& offset)
{
	for (int i = 0; i < NumberOfFrames; i++)
	{
		frameResourceInst[i]->UpdateShadowDescriptorsSpotLight(offset);
	}

	D3D12_DEPTH_STENCIL_VIEW_DESC depthstencilviewdesc = {};
	depthstencilviewdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthstencilviewdesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthstencilviewdesc.Texture2D.MipSlice = 0;


	g_Device->CreateDepthStencilView(GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetSpotLight(offset - NumberOfDirectionalLightsPerScene).GetShadow()->GetResource(), &depthstencilviewdesc,
		DepthStencilView(1 + offset));
}

DXApp_12::~DXApp_12()
{
}


void DXApp_12::privTerminate()
{
	//Must flush before release
	FlushCommandQueue(); //YOU CANNOT RELEASE ITEMS THAT ARE IN A QUEUE

	ReleaseAndDeleteCOMobject(g_DebugController);
	ReleaseAndDeleteCOMobject(g_DXGIFactory);
	ReleaseAndDeleteCOMobject(g_Fence);
	ReleaseAndDeleteCOMobject(g_CommandQueue);

	ReleaseAndDeleteCOMobject(g_RtvHeap);
	ReleaseAndDeleteCOMobject(g_DsvHeap);

	for (UINT i = 0; i < SwapChainBufferCount; i++) {
		ReleaseAndDeleteCOMobject(g_mSwapChainBuffer[i]);
	}

	delete[] g_mSwapChainBuffer;

	ReleaseAndDeleteCOMobject(g_SwapChain);

	ReleaseAndDeleteCOMobject(g_DepthStencilBuffer);

	ReleaseAndDeleteCOMobject(g_RootSig_Particle);
	ReleaseAndDeleteCOMobject(g_RootSig_ColorInstanced);
	ReleaseAndDeleteCOMobject(g_RootSig_ColorShadow);
	ReleaseAndDeleteCOMobject(g_RootSig_TextureInstanced);
	ReleaseAndDeleteCOMobject(g_RootSig_Shadow);
	ReleaseAndDeleteCOMobject(g_SamplerHeap);

	for (int i = 0; i < NumberOfFrames; i++) {
		delete frameResourceInst[i];
	}

	ReleaseAndDeleteCOMobject(g_PreRenderCommandList);
	ReleaseAndDeleteCOMobject(g_PostRenderCommandList);
	ReleaseAndDeleteCOMobject(g_RenderCommandList);
	ReleaseAndDeleteCOMobject(g_ParticleCommandList);
	ReleaseAndDeleteCOMobject(g_ShadowCommandList);


	ShaderManagerAttorney_12::Engine::Terminate();

	ReleaseAndDeleteCOMobject(g_Device);

	delete pInstance;
}

void DXApp_12::InitializeEngineResources() 
{

	//TextureManagerAttorney_12::Engine::Initialize();
	TextureManagerAttorney::Engine::Initialize(g_RenderCommandList);
	ModelManagerAttorney::Engine::Initialize(g_RenderCommandList);
	TerrainObjectManager::Initialize(g_RenderCommandList);

	CD3DX12_DESCRIPTOR_RANGE range[4];

	CD3DX12_ROOT_PARAMETER rootParams[3];

	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;


	ID3D10Blob* serializedSig;
	ID3D10Blob* error;

	HRESULT hr;


	//--------------------------------------------
	//Create Root Sig Color Instanced
	//--------------------------------------------

	range[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	rootParams[0].InitAsDescriptorTable(1, &range[0]);

	rootSigDesc.Init(1, &rootParams[0], 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedSig, &error);
	assert(hr == S_OK);

	hr = g_Device->CreateRootSignature(0, serializedSig->GetBufferPointer(), serializedSig->GetBufferSize(), IID_PPV_ARGS(&g_RootSig_ColorInstanced));

	assert(hr == S_OK);

	//--------------------------------------------
	//Create Root Sig Color Shadow
	//--------------------------------------------

	const CD3DX12_STATIC_SAMPLER_DESC shadowSamp(2, D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
		D3D12_TEXTURE_ADDRESS_MODE_BORDER, D3D12_TEXTURE_ADDRESS_MODE_BORDER, D3D12_TEXTURE_ADDRESS_MODE_BORDER, 
		0.0f, 16, D3D12_COMPARISON_FUNC_LESS_EQUAL);


	range[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1 + NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene, 0);
	range[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene, 0);

	rootParams[0].InitAsDescriptorTable(2, &range[0]);

	rootSigDesc.Init(1, &rootParams[0], 1, &shadowSamp, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedSig, &error);
	assert(hr == S_OK);

	hr = g_Device->CreateRootSignature(0, serializedSig->GetBufferPointer(), serializedSig->GetBufferSize(), IID_PPV_ARGS(&g_RootSig_ColorShadow));

	assert(hr == S_OK);

	//--------------------------------------------
	//Create Root Sig Texture Instanced
	//--------------------------------------------

	range[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	range[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, NumberOfTextures, 0);
	range[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, 0);


	rootParams[0].InitAsDescriptorTable(1, &range[0]);
	rootParams[1].InitAsDescriptorTable(1, &range[1]);
	rootParams[2].InitAsDescriptorTable(1, &range[2]);

	rootSigDesc.Init(3, &rootParams[0], 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedSig, &error);
	assert(hr == S_OK);

	hr = g_Device->CreateRootSignature(0, serializedSig->GetBufferPointer(), serializedSig->GetBufferSize(), IID_PPV_ARGS(&g_RootSig_TextureInstanced));

	assert(hr == S_OK);

	//--------------------------------------------
	//Create Root Sig Particle
	//--------------------------------------------
	range[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	range[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, NumberOfTextures, 0);
	range[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, 0);

	rootParams[0].InitAsDescriptorTable(1, &range[0]);
	rootParams[1].InitAsDescriptorTable(1, &range[1]);
	rootParams[2].InitAsDescriptorTable(1, &range[2]);

	rootSigDesc.Init(3, &rootParams[0], 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedSig, &error);
	assert(hr == S_OK);

	hr = g_Device->CreateRootSignature(0, serializedSig->GetBufferPointer(), serializedSig->GetBufferSize(), IID_PPV_ARGS(&g_RootSig_Particle));

	assert(hr == S_OK);

	//--------------------------------------------
	//Create Root Sig Shadow
	//--------------------------------------------
	range[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	rootParams[0].InitAsDescriptorTable(1, &range[0]);

	rootSigDesc.Init(1, &rootParams[0], 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedSig, &error);
	assert(hr == S_OK);

	hr = g_Device->CreateRootSignature(0, serializedSig->GetBufferPointer(), serializedSig->GetBufferSize(), IID_PPV_ARGS(&g_RootSig_Shadow));

	assert(hr == S_OK);

	//-----------------------------------------------------
	// Create Samplers
	//-----------------------------------------------------

	D3D12_DESCRIPTOR_HEAP_DESC descSamplerHeap = {};
	descSamplerHeap.NumDescriptors = 2;
	descSamplerHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
	descSamplerHeap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	g_Device->CreateDescriptorHeap(&descSamplerHeap, IID_PPV_ARGS(&g_SamplerHeap));

	D3D12_SAMPLER_DESC sampler = {};
	sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
	sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	sampler.MipLODBias = 0;
	sampler.MaxAnisotropy = 0;
	sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	sampler.MinLOD = 0.0f;
	sampler.MaxLOD = D3D12_FLOAT32_MAX;

	DXApp_12::GetDevice()->CreateSampler(&sampler, g_SamplerHeap->GetCPUDescriptorHandleForHeapStart());
	ShaderManagerAttorney_12::Engine::Initialize(GetCommandList(), g_ShadowCommandList);

	descHeaps[0] = frameResourceInst[currentFrame]->GetCBV_SRVDescHeap();
	descHeaps[1] = g_SamplerHeap;
}


void DXApp_12::FlushCommandQueue()
{
	CurrentFence++;
	currentFrame = (currentFrame + 1) % NumberOfFrames;

	HRESULT hr = g_CommandQueue->Signal(g_Fence, CurrentFence);
	assert(hr == S_OK);


	if (g_Fence->GetCompletedValue() < CurrentFence - NumberOfFrames + 1 && (int)(CurrentFence - NumberOfFrames + 1) > 0) {

		HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);
		
		HRESULT hr = g_Fence->SetEventOnCompletion(CurrentFence - NumberOfFrames + 1, eventHandle);
		assert(hr == S_OK);

		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

#pragma region DX12 Create Functions

void DXApp_12::EnableDebugLayer()
{
	HRESULT hr = D3D12GetDebugInterface(IID_PPV_ARGS(&g_DebugController));
	assert(hr == S_OK);
	g_DebugController->EnableDebugLayer();
}

void DXApp_12::CreateDevice()
{
	HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&g_Device));

	assert(hr == S_OK);
}

void DXApp_12::CreateFence()
{
	HRESULT hr = g_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_Fence));
	assert(hr == S_OK);
}


void DXApp_12::QueryDescriptors()
{
	RtvDescriptorSize = g_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	DsvDescriptorSize = g_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	CbvSrvDescriptorSize = g_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void DXApp_12::CheckMSAAQuality()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS qualityLevels;
	qualityLevels.Format = BackBufferFormat;
	qualityLevels.SampleCount = 4;
	qualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	qualityLevels.NumQualityLevels = 0;

	HRESULT hr = g_Device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &qualityLevels, sizeof(qualityLevels));
	assert(hr == S_OK);

	m4xMsaaQuality = qualityLevels.NumQualityLevels;
	assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level");

}

void DXApp_12::CreateCommandObjects() // Create the Queue, List, and Allocator
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	HRESULT hr = g_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&g_CommandQueue));
	assert(hr == S_OK);

	hr = g_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameResourceInst[currentFrame]->GetPreRenderCommandAllocator(), nullptr, IID_PPV_ARGS(&g_PreRenderCommandList));
	assert(hr == S_OK);

	hr = g_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameResourceInst[currentFrame]->GetPostRenderCommandAllocator(), nullptr, IID_PPV_ARGS(&g_PostRenderCommandList));
	assert(hr == S_OK);

	hr = g_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameResourceInst[currentFrame]->GetRenderCommandAllocator(), nullptr, IID_PPV_ARGS(&g_RenderCommandList));
	assert(hr == S_OK);

	hr = g_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameResourceInst[currentFrame]->GetParticleCommandAllocator(), nullptr, IID_PPV_ARGS(&g_ParticleCommandList));
	assert(hr == S_OK);

	hr = g_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameResourceInst[currentFrame]->GetShadowCommandAllocator(), nullptr, IID_PPV_ARGS(&g_ShadowCommandList));
	assert(hr == S_OK);

	hr = g_PreRenderCommandList->Close();
	assert(hr == S_OK);

	hr = g_PostRenderCommandList->Close();
	assert(hr == S_OK);

	hr = g_RenderCommandList->Close();
	assert(hr == S_OK);

	hr = g_ParticleCommandList->Close();
	assert(hr == S_OK);

	hr = g_ShadowCommandList->Close();
	assert(hr == S_OK);
}

void DXApp_12::CreateSwapChain() {
	ReleaseAndDeleteCOMobject(g_SwapChain);

	RECT rect;

	GetClientRect(MainWindow, &rect);

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = rect.right - rect.left;
	sd.BufferDesc.Height = rect.bottom - rect.top;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = BackBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m4xMsaaQuality ? m4xMsaaQuality : 1;
	sd.SampleDesc.Quality = m4xMsaaQuality ? (m4xMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SwapChainBufferCount;
	sd.OutputWindow = MainWindow;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = g_DXGIFactory->CreateSwapChain(g_CommandQueue, &sd, &g_SwapChain);
	assert(hr == S_OK);
}

void DXApp_12::CreateDescriptorHeaps() { //You pull your render targets from heaps. You need to create Render Target Heap and DepthStencil Heap

	//-----------------------------------
	//Create Render Target Heap
	//-----------------------------------
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;

	heapDesc.NumDescriptors = SwapChainBufferCount;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heapDesc.NodeMask = 0;

	HRESULT hr = g_Device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&g_RtvHeap));
	assert(hr == S_OK);

	//-----------------------------------
	//Create Depth Stencil Heap
	//-----------------------------------

	heapDesc.NumDescriptors = 1 + NumberOfDirectionalLightsPerScene + NumberOfSpotLightsPerScene;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

	hr = g_Device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&g_DsvHeap));
	assert(hr == S_OK);
}

D3D12_CPU_DESCRIPTOR_HANDLE DXApp_12::CurrentBackBufferView() const {
	//CD3DX12 constructor: offsets to the RTV of current back buffer	
	// This function just abstracts pointer math?? Not really sure why it is nessecary to use extern lib, but *shrug* frank luna uses it sooo
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		g_RtvHeap->GetCPUDescriptorHandleForHeapStart(), // get gpu heap start
		CurrentBackBuffer, //current buffer is amount to offset
		RtvDescriptorSize
	);
}

D3D12_CPU_DESCRIPTOR_HANDLE DXApp_12::DepthStencilView(int index) const {
	//since we just have one depth buffer, we just return start of heap
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		g_DsvHeap->GetCPUDescriptorHandleForHeapStart(), // get gpu heap start
		index, //current buffer is amount to offset
		DsvDescriptorSize
	);;
}

void DXApp_12::CreateRenderTargetViews() {

	//Here we use the REnder heap we created earlier to create render targets

	g_mSwapChainBuffer = new ID3D12Resource1 * [SwapChainBufferCount];//we will need 2 for now, one front buffer and one back

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(g_RtvHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT i = 0; i < SwapChainBufferCount; i++) {
		HRESULT hr = g_SwapChain->GetBuffer(i, IID_PPV_ARGS(&g_mSwapChainBuffer[i])); //
		assert(hr == S_OK);

		g_Device->CreateRenderTargetView(g_mSwapChainBuffer[i], nullptr, rtvHandle);

		g_mSwapChainBuffer[i]->SetName(L"SwapChainBuffer");

		rtvHandle.Offset(1, RtvDescriptorSize);
	}
}

void DXApp_12::CreateDepthStencilView() {

	RECT rect;

	GetClientRect(MainWindow, &rect);

	D3D12_RESOURCE_DESC dsvDesc;
	dsvDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	dsvDesc.Alignment = 0;
	dsvDesc.Width = rect.right - rect.left;
	dsvDesc.Height = rect.bottom - rect.top;
	dsvDesc.DepthOrArraySize = 1;
	dsvDesc.MipLevels = 1;
	dsvDesc.Format = DepthStencilFormat;
	dsvDesc.SampleDesc.Count = m4xMsaaQuality ? m4xMsaaQuality : 1;
	dsvDesc.SampleDesc.Quality = m4xMsaaQuality ? (m4xMsaaQuality - 1) : 0;
	dsvDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	dsvDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = DepthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	g_Device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&dsvDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(&g_DepthStencilBuffer));

	g_Device->CreateDepthStencilView(g_DepthStencilBuffer, nullptr, DepthStencilView(0));

	GetCommandList()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g_DepthStencilBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	g_DepthStencilBuffer->SetName(L"DepthStencilBuffer");

}

void DXApp_12::SetViewPort() 
{
	RECT rect;

	GetClientRect(MainWindow, &rect);

	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(rect.right - rect.left);
	vp.Height = static_cast<float>(rect.bottom - rect.top);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	scissorRect = rect;

}

#pragma endregion
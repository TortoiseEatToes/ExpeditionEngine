#pragma once

#include <d3d12.h>
#include <dxgi.h>
#include "../../Math/Vector/Vector4F.h"
#include "../../Math/Matrix/Matrix4F.h"
#include <string>
#include "../../Camera/Camera.h"
#include "../FrameResources/FrameResourceInstanced.h"
#include "../Shaders/UploadStructs_12.h"

class ShaderColor_12;
class ShaderColorLight_12;
class ShaderTexture_12;
class LightManager;
class Model_12;
class ShadowMap;

class DXApp_12 : public Align16
{
public:
	static HWND GetWindow()
	{
		return Instance()->MainWindow;
	}

	static void Initialize(HWND hWnd)
	{
		Instance()->privInitialize(hWnd);
	}

	static void FinishRendering()
	{
		Instance()->privFinishRendering();
	}

	static void PrepareToRender()
	{
		Instance()->privPrepareToRender();
	}

	static void Terminate()
	{
		Instance()->privTerminate();
	}

	static void DoneUploadingResources()
	{
		Instance()->privDoneUploadingResources();
	}

	static void StartCleanup() 
	{
		for (int i = 0; i < NumberOfFrames; i++)
		{
			Instance()->FlushCommandQueue();
		}
	}

	static ID3D12Device5*& GetDevice() 
	{
		return Instance()->g_Device;
	}

	static DXGI_FORMAT* GetBackBufferFormat() 
	{
		return &Instance()->BackBufferFormat;
	}

	static DXGI_FORMAT* GetDepthBufferFormat()
	{
		return &Instance()->DepthStencilFormat;
	}

	static int Get4xMSAAQuality() 
	{
		return Instance()->m4xMsaaQuality;
	}

	static int GetCBVDescSize()
	{
		return Instance()->CbvSrvDescriptorSize;
	}

	static FrameResourceInstanced* GetFrameResourceInstanced()
	{
		return Instance()->frameResourceInst[currentFrame];
	}

	static ID3D12RootSignature* GetRootSigColorInstanced()
	{
		return Instance()->g_RootSig_ColorInstanced;
	}

	static ID3D12RootSignature* GetRootSigColorShadow()
	{
		return Instance()->g_RootSig_ColorShadow;
	}

	static ID3D12RootSignature* GetRootSigTextureInstanced()
	{
		return Instance()->g_RootSig_TextureInstanced;
	}

	static ID3D12RootSignature* GetRootSigParticle()
	{
		return Instance()->g_RootSig_Particle;
	}

	static ID3D12RootSignature* GetRootSigShadow()
	{
		return Instance()->g_RootSig_Shadow;
	}

	static ID3D12DescriptorHeap* GetSamplerHeap()
	{
		return Instance()->g_SamplerHeap;
	}

	static float GetHeight() 
	{
		return Instance()->ClientWindowHeight;
	}

	static float GetWidth()
	{
		return Instance()->ClientWindowWidth;
	}

	static ID3D12GraphicsCommandList4* GetCommandList()
	{
		return Instance()->g_RenderCommandList;
	}

	static ID3D12GraphicsCommandList4* GetShadowCommandList()
	{
		return Instance()->g_ShadowCommandList;
	}

	static ID3D12GraphicsCommandList4* GetParticleCommandList()
	{
		return Instance()->g_ParticleCommandList;
	}

	static void SetColorRootSig() 
	{
		Instance()->g_RenderCommandList->SetGraphicsRootSignature(Instance()->g_RootSig_ColorInstanced);
	}

	static void SetColorShadowRootSig()
	{
		Instance()->g_RenderCommandList->SetGraphicsRootSignature(Instance()->g_RootSig_ColorShadow);
	}

	static void SetTextureRootSig()
	{
		Instance()->g_RenderCommandList->SetGraphicsRootSignature(Instance()->g_RootSig_TextureInstanced);
	}

	static void SetParticleRootSig()
	{
		Instance()->g_ParticleCommandList->SetGraphicsRootSignature(Instance()->g_RootSig_Particle);
	}

	static void UpdateTextureDescriptors(CD3DX12_CPU_DESCRIPTOR_HANDLE handle)
	{
		Instance()->privUpdateTextureDescriptors(handle);
	}

	static void UpdateShadowDescriptorsDirectional(const int& offset)
	{
		Instance()->privUpdateShadowDescriptorsDirectional(offset);
	}

	static void UpdateShadowDescriptorsSpotLight(const int& offset)
	{
		Instance()->privUpdateShadowDescriptorsSpotLight(offset);
	}

	static void PrepareToRenderShadows() 
	{
		Instance()->privPrepareToRenderShadows();
	}

	static void PrepareShadow(Shadow* pShadow)
	{
		Instance()->privPrepareShadow(pShadow);
	}

	static void CloseShadow(Shadow* pShadow)
	{
		Instance()->privCloseShadow(pShadow);
	}

	static void FinishRenderingShadows()
	{
		Instance()->privFinishRenderingShadows();
	}

private:


	//-------------------------------------------------------------
	// Engine Resources
	//-------------------------------------------------------------
	
	ID3D12RootSignature* g_RootSig_Particle;
	ID3D12RootSignature* g_RootSig_ColorInstanced;
	ID3D12RootSignature* g_RootSig_ColorShadow;
	ID3D12RootSignature* g_RootSig_TextureInstanced;
	ID3D12RootSignature* g_RootSig_Shadow;

	static const int NumberOfFrames = 3;
	static int currentFrame;
	FrameResourceInstanced* frameResourceInst[NumberOfFrames];
	ID3D12DescriptorHeap* g_SamplerHeap;

	void InitializeEngineResources();
	void privDoneUploadingResources();
	void privFinishRendering();
	void privPrepareToRender();
	void privUpdateTextureDescriptors(CD3DX12_CPU_DESCRIPTOR_HANDLE handle);

	void privPrepareToRenderShadows();
	void privPrepareShadow(Shadow* shadow);
	void privCloseShadow(Shadow* offset);
	void privFinishRenderingShadows();

	void privUpdateShadowDescriptorsDirectional(const int& offset);
	void privUpdateShadowDescriptorsSpotLight(const int& offset);

	ID3D12DescriptorHeap* descHeaps[2];

	//--------------------------------------------------------------
	// Singleton 
	//--------------------------------------------------------------

	static DXApp_12* pInstance;

	static DXApp_12* Instance() {
		if (!pInstance)
			pInstance = new DXApp_12();
		return pInstance;
	}

	DXApp_12();
	DXApp_12(DXApp_12&&) = delete;
	DXApp_12(const DXApp_12&) = delete;
	const DXApp_12& operator = (DXApp_12&&) = delete;
	const DXApp_12& operator = (const DXApp_12&) = delete;
	DXApp_12(HWND& hWnd);
	~DXApp_12();


	void privInitialize(HWND hWnd);
	void privTerminate();

	HWND MainWindow;

	bool appIsRunning = false;

	float BackgroundColor[4] = { 0.000000000f, 0.000000000f, 0.545098066f, 1.000000000f };

	float ClientWindowWidth;
	float ClientWindowHeight;

	//----------------------------------------------------
	// Debug layer Objects
	//----------------------------------------------------

	ID3D12Debug3* g_DebugController = nullptr;
	void EnableDebugLayer();

	//----------------------------------------------------
	// Device Creation
	//----------------------------------------------------
	ID3D12Device5* g_Device = nullptr;
	//IDXGIAdapter1* g_Adapter; Currently using default Adapter only for simplicity.
	void CreateDevice();


	//-----------------------------------
	//Fence and Descriptors
	//-----------------------------------
	ID3D12Fence1* g_Fence = nullptr;
	void CreateFence();

	//----------------------------------
	//Check 4X MSAA Support
	//----------------------------------
	int m4xMsaaQuality;
	void CheckMSAAQuality();

	//------------------------------------
	//Command Queue and List
	//------------------------------------
	ID3D12CommandQueue* g_CommandQueue = nullptr;
	ID3D12GraphicsCommandList4* g_PreRenderCommandList = nullptr;
	ID3D12GraphicsCommandList4* g_PostRenderCommandList = nullptr;
	ID3D12GraphicsCommandList4* g_RenderCommandList = nullptr;
	ID3D12GraphicsCommandList4* g_ParticleCommandList = nullptr;
	ID3D12GraphicsCommandList4* g_ShadowCommandList = nullptr;
	void CreateCommandObjects();

	//---------------------------------------------
	// SwapChain
	//---------------------------------------------
	DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	UINT SwapChainBufferCount = 2;

	IDXGISwapChain* g_SwapChain = nullptr;
	void CreateSwapChain();

	int CurrentBackBuffer = 0;

	//----------------------------------------
	//Create Descriptor Heaps
	//----------------------------------------
	int RtvDescriptorSize; // Render Target Descriptor
	int DsvDescriptorSize; // Depth Buffer Descriptor
	int CbvSrvDescriptorSize; // Constant Buffs, Shader Resource Descriptor
	void QueryDescriptors();

	void CreateDescriptorHeaps();
	ID3D12DescriptorHeap* g_RtvHeap = nullptr; //RenderTarget
	ID3D12DescriptorHeap* g_DsvHeap = nullptr; //Depth Buffer

	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView(int index) const;

	//-------------------------------------
	// Render Target View
	//-------------------------------------
	ID3D12Resource1** g_mSwapChainBuffer;
	void CreateRenderTargetViews();

	//--------------------------------------
	// Depth Stencil buffer
	//--------------------------------------
	ID3D12Resource1* g_DepthStencilBuffer;
	void CreateDepthStencilView();
	DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//-------------------------------
	//Factory
	//-------------------------------
	IDXGIFactory1* g_DXGIFactory = nullptr;

	//---------------------------------
	// Viewport
	//---------------------------------
	void SetViewPort();
	D3D12_VIEWPORT vp;
	tagRECT scissorRect;

	//---------------------------------
	// Sync GPU/CPU
	//---------------------------------
	UINT64 CurrentFence = 0;
	void FlushCommandQueue();
};



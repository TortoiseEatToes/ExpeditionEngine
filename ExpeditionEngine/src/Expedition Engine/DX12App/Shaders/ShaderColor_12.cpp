#include "ShaderColor_12.h"
#include "../d3dUtil_12.h"
#include <assert.h>
#include "../d3dx12.h"
#include "../DXApp/DXApp_12.h"
#include "../../../Expedition Resources/EngineSettings.h"
#include "../FrameResources/FrameResourceInstanced.h"

ShaderColor_12::ShaderColor_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList)
	: ShaderBase_12(device, cmdList, L"Assets\\Shaders\\g_Color.hlsl")
{
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
				
		{"INSTANCE_WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 128, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
	
	};

	mpVertexLayout.NumElements = sizeof(inputLayout) / sizeof(D3D12_INPUT_ELEMENT_DESC);
	mpVertexLayout.pInputElementDescs = inputLayout;

	name = ShaderName::Color;

	CreatePipeline();
}

ShaderColor_12::~ShaderColor_12()
{
	ReleaseAndDeleteCOMobject(g_PSO);
}

void ShaderColor_12::PrepareToRender(ID3D12GraphicsCommandList4* cmdList) {

	cmdList->SetPipelineState(g_PSO);
	
	cmdList->SetGraphicsRootDescriptorTable(0, DXApp_12::GetFrameResourceInstanced()->GetGPUHandle_PerFrame());
	cmdList->IASetVertexBuffers(1, 1, &DXApp_12::GetFrameResourceInstanced()->GetVBV_Object());
}

void ShaderColor_12::CreatePipeline()
{
	//-------------------------------------------------
	// Create rasterizer state
	//-------------------------------------------------

	D3D12_RASTERIZER_DESC rd = {}; //Rasterizer desc, this is passed to the pipeline. Everything is the defaults excepy CCW.
	rd.FillMode = D3D12_FILL_MODE_SOLID; // default = D3D12_FILL_SOLID
	rd.FrontCounterClockwise = true; // DEFAULT = FALSE
	rd.CullMode = D3D12_CULL_MODE_BACK;
	rd.DepthBias = 0;
	rd.DepthBiasClamp = 0.0f;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthClipEnable = true;
	rd.MultisampleEnable = false;
	rd.AntialiasedLineEnable = false;
	rd.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	rd.ForcedSampleCount = 0;

	//--------------------------------------------------------
	// Create Root Sig
	//--------------------------------------------------------

	int m4xMsaaQuality = DXApp_12::Get4xMSAAQuality();

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

	psoDesc.pRootSignature = DXApp_12::GetRootSigColorInstanced();
	psoDesc.InputLayout = mpVertexLayout;
	psoDesc.VS = { pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize() };
	psoDesc.PS = { pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize() };
	psoDesc.RasterizerState = rd; //CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = *(DXApp_12::GetBackBufferFormat());
	psoDesc.SampleDesc.Count = m4xMsaaQuality? m4xMsaaQuality : 1;
	psoDesc.SampleDesc.Quality = m4xMsaaQuality ? (m4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = *DXApp_12::GetDepthBufferFormat();

	HRESULT hr = mDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&g_PSO));

	assert(hr == S_OK);
}


#include "ShaderTexture_12.h"
#include <assert.h>
#include "../d3dx12.h"
#include "../d3dUtil_12.h"
#include "../FrameResources/FrameResourceInstanced.h"

ShaderTexture_12::ShaderTexture_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList)
	: ShaderBase_12(device, cmdList, L"Assets\\Shaders\\g_Texture.hlsl")
{
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

		{"INSTANCE_WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLDINVERSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLDINVERSE", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 80, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLDINVERSE", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 96, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLDINVERSE", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 112, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_TEXTURE", 0, DXGI_FORMAT_R32_UINT, 1, 176, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
	};

	mpVertexLayout.NumElements = sizeof(inputLayout) / sizeof(D3D12_INPUT_ELEMENT_DESC);
	mpVertexLayout.pInputElementDescs = inputLayout;

	name = ShaderName::TextureShader;

	CreatePipeline();
}


ShaderTexture_12::~ShaderTexture_12()
{
}

void ShaderTexture_12::UpdateTexture(TextureName tex)
{
	//DXApp_12::GetFrameResourceInstanced()->SetTexture_ShaderTexture(tex);
}

void ShaderTexture_12::PrepareToRender(ID3D12GraphicsCommandList4* cmdList)
{
	cmdList->SetPipelineState(g_PSO);
	
	cmdList->SetGraphicsRootDescriptorTable(0, DXApp_12::GetFrameResourceInstanced()->GetGPUHandle_PerFrame());
	cmdList->SetGraphicsRootDescriptorTable(1, DXApp_12::GetFrameResourceInstanced()->GetGPUHandle_TextureHeap());
	cmdList->SetGraphicsRootDescriptorTable(2, DXApp_12::GetSamplerHeap()->GetGPUDescriptorHandleForHeapStart());
	
	cmdList->IASetVertexBuffers(1, 1, &DXApp_12::GetFrameResourceInstanced()->GetVBV_Object());
}

void ShaderTexture_12::CreatePipeline()
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


	//------------------------------------------------------
	//Create Pipeline
	//------------------------------------------------------

	int m4xMsaaQuality = DXApp_12::Get4xMSAAQuality();

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

	psoDesc.pRootSignature = DXApp_12::GetRootSigTextureInstanced();
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
	psoDesc.SampleDesc.Count = m4xMsaaQuality ? m4xMsaaQuality : 1;
	psoDesc.SampleDesc.Quality = m4xMsaaQuality ? (m4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = *DXApp_12::GetDepthBufferFormat();

	HRESULT hr = mDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&g_PSO));

	assert(hr == S_OK);
}

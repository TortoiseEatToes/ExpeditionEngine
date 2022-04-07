#include "ShaderParticle_12.h"
#include "../DXApp/DXApp_12.h"
#include "../d3dx12.h"

ShaderParticle_12::~ShaderParticle_12()
{
}

ShaderParticle_12::ShaderParticle_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList)
	: ShaderBase_12(device, cmdList, L"Assets\\Shaders\\g_ParticleShader_12.hlsl", "vs_5_1", "ps_5_1")
{
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

		{"INSTANCE_WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_TINT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
		{"INSTANCE_TEXTURE", 0, DXGI_FORMAT_R32_UINT, 1, 80, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
	};

	mpVertexLayout.NumElements = sizeof(inputLayout) / sizeof(D3D12_INPUT_ELEMENT_DESC);
	mpVertexLayout.pInputElementDescs = inputLayout;

	name = ShaderName::ParticleShader;

	CreatePipeline();

	g_CmdList = DXApp_12::GetParticleCommandList();
}

void ShaderParticle_12::UpdateTexture(TextureName tex)
{
	//DXApp_12::GetFrameResourceInstanced()->SetTexture_ShaderParticle(tex);
}

void ShaderParticle_12::PrepareToRender(ID3D12GraphicsCommandList4* cmdList)
{
	cmdList->SetPipelineState(g_PSO);
	
	cmdList->SetGraphicsRootDescriptorTable(0, DXApp_12::GetFrameResourceInstanced()->GetGPUHandle_PerFrame());
	cmdList->SetGraphicsRootDescriptorTable(1, DXApp_12::GetFrameResourceInstanced()->GetGPUHandle_TextureHeap());
	cmdList->SetGraphicsRootDescriptorTable(2, DXApp_12::GetSamplerHeap()->GetGPUDescriptorHandleForHeapStart());
	
	cmdList->IASetVertexBuffers(1, 1, &DXApp_12::GetFrameResourceInstanced()->GetVBV_Particle());

	float blendFactor = 0.2f;

	FLOAT bf[] = { blendFactor, blendFactor, blendFactor, 1.0f };

	cmdList->OMSetBlendFactor(bf);
}

void ShaderParticle_12::CreatePipeline()
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


	//-------------------------------------------
	// blend state
	//-------------------------------------------

	D3D12_BLEND_DESC bs = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	bs.AlphaToCoverageEnable = true;
	bs.IndependentBlendEnable = true;

	D3D12_RENDER_TARGET_BLEND_DESC rtbs = {};
	rtbs.BlendEnable = true;
	rtbs.SrcBlend = D3D12_BLEND_BLEND_FACTOR;
	rtbs.DestBlend = D3D12_BLEND_INV_BLEND_FACTOR;
	rtbs.BlendOp = D3D12_BLEND_OP_ADD;
	rtbs.SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
	rtbs.DestBlendAlpha = D3D12_BLEND_INV_SRC_ALPHA;
	rtbs.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	rtbs.LogicOpEnable = false;
	rtbs.LogicOp = D3D12_LOGIC_OP_NOOP;
	rtbs.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	
	bs.RenderTarget[0] = rtbs;

	//------------------------------------------------------
	//Create Pipeline
	//------------------------------------------------------

	int m4xMsaaQuality = DXApp_12::Get4xMSAAQuality();

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

	psoDesc.pRootSignature = DXApp_12::GetRootSigParticle();
	psoDesc.InputLayout = mpVertexLayout;
	psoDesc.VS = { pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize() };
	psoDesc.PS = { pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize() };
	psoDesc.RasterizerState = rd; //CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = bs;
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

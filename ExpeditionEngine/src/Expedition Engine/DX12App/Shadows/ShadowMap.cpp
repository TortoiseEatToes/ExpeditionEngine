#include "ShadowMap.h"
#include "../d3dUtil_12.h"

ShadowMap::ShadowMap(ID3D12Device5* inDevice) : device(inDevice)
{
}

ShadowMap::~ShadowMap()
{
	ReleaseAndDeleteCOMobject(g_ShadowMap);
}

unsigned int ShadowMap::GetWidth() const
{
	return width;
}

unsigned int ShadowMap::GetHeight() const
{
	return height;
}

ID3D12Resource1* ShadowMap::GetResource()
{
	return g_ShadowMap;
}

D3D12_VIEWPORT* ShadowMap::GetViewport()
{
	return &g_ViewPort;
}

D3D12_RECT* ShadowMap::GetScissorRect()
{
	return &g_ScissorRect;
}

void ShadowMap::BuildResources(unsigned int inWidth, unsigned int inHeight)
{
	ReleaseAndDeleteCOMobject(g_ShadowMap);

	width = inWidth;
	height = inHeight;

	g_ViewPort = { 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 1.0f };
	g_ScissorRect = { 0,0, static_cast<int>(width), static_cast<int>(height) };

	D3D12_RESOURCE_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(D3D12_RESOURCE_DESC));

	texDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texDesc.Alignment = 0;
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.DepthOrArraySize = 1;
	texDesc.MipLevels = 1;
	texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	texDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	HRESULT hr = device->CreateCommittedResource1(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &texDesc, D3D12_RESOURCE_STATE_GENERIC_READ, &optClear, nullptr, IID_PPV_ARGS(&g_ShadowMap));

}

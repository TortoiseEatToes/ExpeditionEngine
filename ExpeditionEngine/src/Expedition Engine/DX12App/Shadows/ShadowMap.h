#pragma once

#include <d3d12.h>
#include "../d3dx12.h"
#include "../../Math/Matrix/Matrix4F.h"

struct ShadowCBData
{
	Matrix4F View;
	Matrix4F Projection;
};



class ShadowMap
{
public:
	ShadowMap(ID3D12Device5* inDevice);
	~ShadowMap();

#pragma region DeletedFunctions

	ShadowMap() = delete;
	ShadowMap(ShadowMap&&) = delete;
	ShadowMap(const ShadowMap&) = delete;
	const ShadowMap& operator = (ShadowMap&&) = delete;
	const ShadowMap& operator = (const ShadowMap&) = delete;

#pragma endregion

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	ID3D12Resource1* GetResource();

	D3D12_VIEWPORT* GetViewport();
	D3D12_RECT* GetScissorRect();

	void BuildResources(unsigned int newWidth, unsigned int newHeight);

private:
	ID3D12Device5* device;

	D3D12_VIEWPORT g_ViewPort;
	D3D12_RECT g_ScissorRect;

	unsigned int height;
	unsigned int width;

	DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	ID3D12Resource1* g_ShadowMap = nullptr;
};


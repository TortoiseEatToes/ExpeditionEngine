#include "Texture.h"
#include "../../DX12App/d3dUtil_12.h"
#include <assert.h>
#include "../../../Expedition Resources/EngineSettings.h"
#include "../../DX12App/Model/DDSTextureLoader.h"
#include "../../DX12App/DXApp/DXApp_12.h"


Texture::~Texture()
{
	ReleaseAndDeleteCOMobject(g_Resource);
	ReleaseAndDeleteCOMobject(g_UploadHeap);
}

Texture::Texture(LPCWSTR filepath, ID3D12GraphicsCommandList4* cmdList, TextureName initName,  UINT isotropic_level, bool ComputeMip, size_t miplevel)
{
	g_Resource = nullptr;
	g_UploadHeap = nullptr;

	name = initName;

	std::wstring fpath(filepath);
	std::wstring ext = fpath.substr(fpath.find_last_of(L".") + 1);

	if (ext == L"dds" || ext == L"DDS") {

		HRESULT hr = DirectX::CreateDDSTextureFromFile12(DXApp_12::GetDevice(), cmdList, filepath, g_Resource, g_UploadHeap);

		assert(hr == S_OK);

		textureWidth = static_cast<int>(g_Resource->GetDesc().Width);
		textureHeight = g_Resource->GetDesc().Height;
	}
}


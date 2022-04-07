#include "TextureManager.h"
#include "../Texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../../../Expedition Resources/EngineSettings.h"
#include "../../../DX12App/DXApp/DXApp_12.h"
#include "../../../DX12App/d3dUtil_12.h"


TextureManager* TextureManager::pInstance = nullptr;

void TextureManager::Initialize(ID3D12GraphicsCommandList4* cmdList) {
	pInstance = new TextureManager();
	Instance().loadCmdList = cmdList;

	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = NumberOfTextures;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	DXApp_12::GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&(Instance().g_SRVDescHeap)));

	Instance().privLoad(TextureName::Default, L"Assets/Textures/Default.dds");
}

TextureManager::TextureManager()
{

}


TextureManager::~TextureManager()
{
	for (int i = 0; i < NumberOfTextures; i++) {
		delete textureArray[i];
	}

	ReleaseAndDeleteCOMobject(g_SRVDescHeap);
}

void TextureManager::Terminate() {
	delete pInstance;
	pInstance = nullptr;
}

Texture* TextureManager::privGet(const TextureName& key) {
	return textureArray[key];
}



void TextureManager::privLoad(const TextureName& key, const wchar_t* path) {

	if (textureArray[key])
		delete textureArray[key];
	textureArray[key] = new Texture(path, loadCmdList, key);

	if (textureArray[key]->GetResource()) {
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle(g_SRVDescHeap->GetCPUDescriptorHandleForHeapStart());
		handle.Offset(key, DXApp_12::GetCBVDescSize());

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = textureArray[key]->GetResource()->GetDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = textureArray[key]->GetResource()->GetDesc().MipLevels;
		srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

		DXApp_12::GetDevice()->CreateShaderResourceView(textureArray[key]->GetResource(), &srvDesc, handle);

		DXApp_12::UpdateTextureDescriptors(GetCPUTextureHandle());
	}
}

wchar_t * TextureManager::addDefaultPath(const wchar_t* path) {

	const int BUFFER_SIZE = 100;

	assert(wcslen(path) + wcslen(defaultPath) < BUFFER_SIZE - 1);

	wchar_t* tmp = new wchar_t[BUFFER_SIZE];

	wcsncpy_s(tmp, BUFFER_SIZE, defaultPath, wcslen(defaultPath));

	wcsncat_s(tmp, BUFFER_SIZE, path, wcslen(path));

	return tmp;
}

CD3DX12_GPU_DESCRIPTOR_HANDLE TextureManager::GetGPUTextureHandle(const TextureName& key)
{
	CD3DX12_GPU_DESCRIPTOR_HANDLE handle(Instance().g_SRVDescHeap->GetGPUDescriptorHandleForHeapStart());
	handle.Offset(key, DXApp_12::GetCBVDescSize());

	return handle;
}

CD3DX12_CPU_DESCRIPTOR_HANDLE TextureManager::GetCPUTextureHandle()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE handle(Instance().g_SRVDescHeap->GetCPUDescriptorHandleForHeapStart());

	return handle;
}
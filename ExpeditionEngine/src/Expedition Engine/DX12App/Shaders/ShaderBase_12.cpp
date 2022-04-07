#include "ShaderBase_12.h"
#include "../d3dUtil_12.h"
#include <d3dcompiler.h>
#include <string>
#include <assert.h>
#include "../d3dx12.h"
#include "../DXApp/DXApp_12.h"


ShaderBase_12::ShaderBase_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList, const WCHAR* filename, LPCSTR vsModel, LPCSTR psModel)
	: mDevice(device), g_CmdList(cmdList)
{
	assert(device != nullptr);
	assert(cmdList != nullptr);

	privBuildShaders(filename, vsModel, psModel);

	//name = shaderName;

}

ID3D12Device* ShaderBase_12::GetDevice() 
{ 
	assert(mDevice != nullptr && "ERROR: Device not set.");
	return mDevice; 
}

ID3D12GraphicsCommandList4* ShaderBase_12::GetCommandList()
{ 
	assert(g_CmdList != nullptr && "ERROR: Context not set.");
	return g_CmdList; 
}

ShaderBase_12::~ShaderBase_12()
{ 
	ReleaseAndDeleteCOMobject(pVSBlob);
	ReleaseAndDeleteCOMobject(pPSBlob);
	ReleaseAndDeleteCOMobject(g_PSO);
}  

// Compile and send the VS and PS shaders to the GPU
void ShaderBase_12::privBuildShaders(const WCHAR* filename, LPCSTR vsModel, LPCSTR psModel)
{
	pVSBlob = CompileShader(filename, nullptr, "VS", vsModel);
	pPSBlob = CompileShader(filename, nullptr, "PS", psModel);
} 



ID3DBlob* ShaderBase_12::CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target)
{
	UINT compileFlags = 0;

	//#if defined(DEBUG) || defined (_DEBUG)
	//	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	//#endif

	HRESULT hr = S_OK;

	ID3DBlob* byteCode = nullptr;
	ID3DBlob* error;

	

	hr = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypoint.c_str(),
		target.c_str(), D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES, 0, &byteCode, &error);

	if (error != nullptr) {
		OutputDebugStringA((char*)error->GetBufferPointer());
	}

	assert(hr == S_OK);

	return byteCode;
}
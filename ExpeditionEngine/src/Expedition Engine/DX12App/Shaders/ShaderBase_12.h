// ShaderBase
// AB, June 2016

#ifndef _ShaderBase_12
#define _ShaderBase_12

#include <d3dcommon.h>
#include "../../Math/Vector/Vector4F.h"
#include <string>
#include <list>
#include "../../../Expedition Resources/ShaderSettings.h"
#include <d3d12.h>

class ShaderBase_12 : public Align16
{
	friend class ShaderBaseAttorney;
private:

	ID3DBlob* CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);
	void privBuildShaders(const WCHAR* filename, LPCSTR vsModel, LPCSTR psModel);

	virtual void CreatePipeline() = 0;	


protected:
	ShaderBase_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList, const WCHAR* filename, LPCSTR vsModel = "vs_5_1", LPCSTR psModel = "ps_5_1");

	// Actual objects managed by this class
	D3D12_INPUT_LAYOUT_DESC     mpVertexLayout;

	// Store these pointers to avoid passing them in every method
	ID3D12Device* mDevice;
	ID3D12GraphicsCommandList4* g_CmdList;

	// Needed for building shaders
	ID3DBlob* pVSBlob;
	ID3DBlob* pPSBlob;

	//Pipelien state
	ID3D12PipelineState* g_PSO;

	ShaderName name;


public:
	ShaderBase_12(const ShaderBase_12&) = delete;				  // Copy constructor
	ShaderBase_12(ShaderBase_12&&) = delete;                    // Move constructor
	ShaderBase_12& operator=(const ShaderBase_12&) & = delete;  // Copy assignment operator
	ShaderBase_12& operator=(ShaderBase_12&&) & = delete;       // Move assignment operator
	ShaderBase_12() = delete;
	virtual ~ShaderBase_12();


	ID3D12GraphicsCommandList4* GetCommandList();

	ID3D12Device* GetDevice();

	ShaderName getShaderName() { return name; }

	virtual void PrepareToRender(ID3D12GraphicsCommandList4* cmdList) = 0;
};


#endif _ShaderBase_12
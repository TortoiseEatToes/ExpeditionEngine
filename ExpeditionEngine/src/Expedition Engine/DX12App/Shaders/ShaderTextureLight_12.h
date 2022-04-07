#ifndef ShaderTextureLight_h
#define ShaderTextureLight_h

#include "ShaderBase_12.h"
#include "../DXApp/DXApp_12.h"
#include "UploadStructs_12.h"
#include "../../../Expedition Resources/TextureSettings.h"

class ShaderTextureLight_12 : public ShaderBase_12
{
public:
	ShaderTextureLight_12() = delete;
	ShaderTextureLight_12(const ShaderTextureLight_12&) = delete;
	ShaderTextureLight_12& operator = (const ShaderTextureLight_12&) = delete;
	~ShaderTextureLight_12();

	ShaderTextureLight_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList);

	void UpdateTexture(TextureName tex);

	void PrepareToRender(ID3D12GraphicsCommandList4* cmdList);

private:
	void CreateConstantBuffer() {};
	void CreatePipeline();
};

#endif ShaderTextureLight_h


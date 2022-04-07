#ifndef ShaderTexture_h
#define ShaderTexture_h

#include "ShaderBase_12.h"
#include "../DXApp/DXApp_12.h"
#include "UploadStructs_12.h"
#include "../../../Expedition Resources/TextureSettings.h"

class ShaderTexture_12 : public ShaderBase_12
{
public:
	ShaderTexture_12() = delete;
	ShaderTexture_12(const ShaderTexture_12&) = delete;
	ShaderTexture_12& operator = (const ShaderTexture_12&) = delete;
	~ShaderTexture_12();

	ShaderTexture_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList);

	void UpdateTexture(TextureName tex);

	void PrepareToRender(ID3D12GraphicsCommandList4* cmdList);

private:
	void CreateConstantBuffer() {};
	void CreatePipeline();
};

#endif ShaderTexture_h


#pragma once

#include "ShaderBase_12.h"
#include "../../../Expedition Resources/TextureSettings.h"

class ShaderParticle_12 : public ShaderBase_12
{
public:
	ShaderParticle_12() = delete;
	ShaderParticle_12(ShaderParticle_12&&) = delete;
	ShaderParticle_12(const ShaderParticle_12&) = delete;
	const ShaderParticle_12& operator = (ShaderParticle_12&&) = delete;
	const ShaderParticle_12& operator = (const ShaderParticle_12&) = delete;
	~ShaderParticle_12();

	ShaderParticle_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList);

	void UpdateTexture(TextureName tex);

	void PrepareToRender(ID3D12GraphicsCommandList4* cmdList);

private:
	void CreateConstantBuffer() {};
	void CreatePipeline();

};


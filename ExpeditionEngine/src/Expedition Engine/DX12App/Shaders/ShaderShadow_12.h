
#ifndef _ShaderShadow_12
#define _ShaderShadow_12

#include "ShaderBase_12.h"
#include "../../Math/Matrix/Matrix4F.h"
#include "UploadStructs_12.h"

class ShaderShadow_12 : public ShaderBase_12
{
public:
	ShaderShadow_12(const ShaderShadow_12&) = delete;				 // Copy constructor
	ShaderShadow_12(ShaderShadow_12&&) = default;                    // Move constructor
	ShaderShadow_12& operator=(const ShaderShadow_12&) = default;  // Copy assignment operator
	ShaderShadow_12& operator=(ShaderShadow_12&&) = default;       // Move assignment operator
	~ShaderShadow_12();		  							         // Destructor

	ShaderShadow_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList);

	static const int MaxInstanceCount = 200;

	void PrepareToRender(ID3D12GraphicsCommandList4* cmdList);

private:
	void CreateConstantBuffer() {};
	void CreatePipeline();
};

#endif _ShaderShadow_12

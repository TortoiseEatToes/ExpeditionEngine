
#ifndef _ShaderColor_12
#define _ShaderColor_12

#include "ShaderBase_12.h"
#include "../../Math/Matrix/Matrix4F.h"
#include "UploadStructs_12.h"



class ShaderColor_12 : public ShaderBase_12
{
public:
	ShaderColor_12(const ShaderColor_12&) = delete;				 // Copy constructor
	ShaderColor_12(ShaderColor_12&&) = default;                    // Move constructor
	ShaderColor_12& operator=(const ShaderColor_12&) & = default;  // Copy assignment operator
	ShaderColor_12& operator=(ShaderColor_12&&) & = default;       // Move assignment operator
	~ShaderColor_12();		  							         // Destructor

	ShaderColor_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList);

	static const int MaxInstanceCount = 200;

	void PrepareToRender(ID3D12GraphicsCommandList4* cmdList);

private:
	void CreateConstantBuffer() {};
	void CreatePipeline();
};

#endif _ShaderColor_12

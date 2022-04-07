// ShaderColorLight
// Andre Berthiaume, Feb 2017

#ifndef _ShaderColorLight
#define _ShaderColorLight

#include "ShaderBase_12.h"

#include "UploadStructs_12.h"
#include "../../Graphics/Light/Light.h"

class Matrix4FDoubleBuffer;

class ShaderColorLight_12 : public ShaderBase_12
{

public:
	ShaderColorLight_12(const ShaderColorLight_12&) = delete;				 // Copy constructor
	ShaderColorLight_12(ShaderColorLight_12&&) = default;                    // Move constructor
	ShaderColorLight_12& operator=(const ShaderColorLight_12&) & = default;  // Copy assignment operator
	ShaderColorLight_12& operator=(ShaderColorLight_12&&) & = default;       // Move assignment operator
	~ShaderColorLight_12();		  							         // Destructor

	ShaderColorLight_12(ID3D12Device5* device, ID3D12GraphicsCommandList4* cmdList);
	void PrepareToRender(ID3D12GraphicsCommandList4* cmdList);

private:
	void CreateConstantBuffer() {};
	void CreatePipeline();

};

#endif _ShaderColorLight


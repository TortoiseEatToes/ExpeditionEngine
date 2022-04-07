#include "ShaderManager_12.h"
#include "ShaderBase_12.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ShaderColorLight_12.h"
#include "ShaderTexture_12.h"
#include "ShaderColor_12.h"
#include "ShaderParticle_12.h"
#include "ShaderBaseAttorney_12.h"
#include "ShaderTextureLight_12.h"
#include "ShaderShadow_12.h"
#include "../DXApp/DXApp_12.h"

ShaderManager_12* ShaderManager_12::shadeInstance = nullptr;

void ShaderManager_12::Initialize(ID3D12GraphicsCommandList4* cmdList, ID3D12GraphicsCommandList4* shadowCmdList) {

	Instance().shaderArray = new ShaderBase_12*[NumberOfShaders] {0};

	ShaderManager_12::Load(new ShaderTexture_12(DXApp_12::GetDevice(), cmdList));
	ShaderManager_12::Load(new ShaderColor_12(DXApp_12::GetDevice(),cmdList));
	ShaderManager_12::Load(new ShaderParticle_12(DXApp_12::GetDevice(), cmdList));
	ShaderManager_12::Load(new ShaderColorLight_12(DXApp_12::GetDevice(), cmdList));
	ShaderManager_12::Load(new ShaderTextureLight_12(DXApp_12::GetDevice(), cmdList));
	ShaderManager_12::Load(new ShaderShadow_12(DXApp_12::GetDevice(), shadowCmdList));
}

ShaderManager_12::ShaderManager_12()
{


}


ShaderManager_12::~ShaderManager_12()
{
	for (int i = 0; i < NumberOfShaders; i++) {
		if(shaderArray[i])
			delete shaderArray[i];
	}
	delete shaderArray;

}

void ShaderManager_12::Terminate() {

	delete shadeInstance;
	shadeInstance = nullptr;
}

ShaderBase_12* ShaderManager_12::privGet(const ShaderName& key) {

	return shaderArray[static_cast<int>(key)];
}



void ShaderManager_12::privLoad(ShaderBase_12* shader) {

	shaderArray[static_cast<int>(shader->getShaderName())] = shader;
}



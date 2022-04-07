#ifndef	ShaderBaseAttorney_h
#define	ShaderBaseAttorney_h

#include "ShaderBase_12.h"


class ShaderBaseAttorney_12 {
	friend class ShaderManager;
	friend class GraphicsScene;

	static void PrepareToRender(ShaderBase_12* shader, ID3D12GraphicsCommandList4* cmdList) { shader->PrepareToRender(cmdList); }
};

#endif 	ShaderBaseAttorney_h

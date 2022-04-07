#ifndef  ShaderManagerAttorney_h
#define ShaderManagerAttorney_h

#include "ShaderManager_12.h"

struct ID3D12GraphicsCommandList4;

class ShaderManagerAttorney_12 {

public:

	class Engine {
		friend class DXApp_12;
		static void Initialize(ID3D12GraphicsCommandList4* cmdList, ID3D12GraphicsCommandList4* shadowCmdList) { ShaderManager_12::Initialize(cmdList, shadowCmdList); }
		static void Terminate() { ShaderManager_12::Terminate(); }
	};

};


#endif ShaderManagerAttorney_h


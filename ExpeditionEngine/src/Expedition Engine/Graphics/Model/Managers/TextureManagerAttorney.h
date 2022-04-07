#ifndef  TextureManagerAttorney_h
#define TextureManagerAttorney_h

#include "TextureManager.h"

class TextureManagerAttorney {

public:

	class Engine {
		friend class ExpeditionEngine;
		friend class DXApp_12;
		static void Initialize(ID3D12GraphicsCommandList4* cmdList) { TextureManager::Initialize(cmdList); }
		static void Terminate() { TextureManager::Terminate(); }
	};

};


#endif TextureManagerAttorney_h


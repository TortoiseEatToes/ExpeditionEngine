#ifndef  ModelManagerAttorney_h
#define ModelManagerAttorney_h

#include "ModelManager.h"

class ModelManagerAttorney {

public:

	class Engine {
		friend class ExpeditionEngine;
		friend class DXApp_12;
		static void Initialize(ID3D12GraphicsCommandList4* cmdList) { ModelManager::Initialize(cmdList); }
		static void Terminate() { ModelManager::Terminate(); }
	};

};


#endif ModelManagerAttorney_h


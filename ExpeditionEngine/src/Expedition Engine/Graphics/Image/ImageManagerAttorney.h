#ifndef  ImageManagerAttorney_h
#define ImageManagerAttorney_h

#include "ImageManager.h"

class ImageManagerAttorney {

public:

	class Engine {
		friend class ExpeditionEngine;
		static void Initialize(){ ImageManager::Initialize(); }
		static void Terminate() { ImageManager::Terminate(); }
	};

};


#endif ImageManagerAttorney_h


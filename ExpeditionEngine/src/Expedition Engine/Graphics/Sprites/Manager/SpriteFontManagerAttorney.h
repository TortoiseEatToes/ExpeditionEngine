#ifndef  SpriteFontManagerAttorney_h
#define SpriteFontManagerAttorney_h

#include "SpriteFontManager.h"

class SpriteFontManagerAttorney {

public:

	class Engine {
		friend class ExpeditionEngine;
		static void Initialize() { SpriteFontManager::Initialize(); }
		static void Terminate() { SpriteFontManager::Terminate(); }
	};

};


#endif SpriteFontManagerAttorney_h


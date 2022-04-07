#ifndef ScreenLogAttorney_h
#define ScreenLogAttorney_h

#include "ScreenLog.h"

class ScreenLogAttorney {

public:

	class Engine {
		friend class ExpeditionEngine;

		static void Terminate() { ScreenLog::Terminate(); }
		static void Render() { ScreenLog::Instance().Render(); }
	};

};

#endif ScreenLogAttorney_h


#ifndef	TerrainAttorney_h
#define TerrainAttorney_h  

#include "Terrain.h"

class TerrainAttorney {
	friend class TerrainManager;

	static void SubmitDrawRegistration(Terrain* pTerrain) { pTerrain->SubmitDrawRegistration(); }
	static void SubmitDrawDeregistration(Terrain* pTerrain) { pTerrain->SubmitDrawDeregistration(); }

};

#endif	TerrainAttorney_h
#ifndef TerrainModelAttorney_h
#define TerrainModelAttorney_h

#include "TerrainModel.h"
#include "../../Math/Vector/Vector4F.h"

class TerrainModelAttorney {

public:
	class TerrainClass 
	{
		friend class GO_Data_ColorLight;
		friend class GO_Data_Texture;
		friend class GO_Data_TextureLight;
		friend class GO_Data_Base;

		static Model* GetModel(TerrainModel* terrain) { return (terrain->pModTerrain); }
		//static void ShowCollision(TerrainModel* terrain, const Vector4F& pos) { terrain->ShowCollision(pos); }
		//static void ShowCollision(TerrainModel* terrain, const Vector4F& max, const Vector4F& min) { terrain->ShowCollision(max, min); };

	};
};

#endif //!TerrainModelAttorney_h

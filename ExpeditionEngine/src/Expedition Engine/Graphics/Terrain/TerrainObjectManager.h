#ifndef TerrainObjectManager_H
#define TerrainObjectManager_H


#include <Windows.h>
#include <d3d12.h>

#include "../../../Expedition Resources/TerrainSettings.h"


class Vect;
class TerrainModel;

/////////////////////////////////
/// \ingroup ASSET
/// \{
////////////////////////////////////
/// Used to load and retrieve Terrains
////////////////////////////////////

class TerrainObjectManager
{
	friend class TerrainObjectManagerAttorney;
public:



	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Function used to retrieve a loaded Terrain
	///
	///	Get(TerrainKey& key) takes in a string and returns a pointer to the Terrain that was loaded with that string as the
	///	key. If no Terrain with given key exists, an error is thrown. This is a static function and can be 
	///	called with TerrainManager::Get(key).
	///
	///	\param key the key of the Terrain that is going to be returned
	///
	/// \par Example:
	///	If a Terrain is loaded in Load Resources as such:
	///		\code
	///		
	///		TerrainObjectManager::Load("loadedTerrain", "sampleTerrain.tga");
	///		
	///		\endcode
	/// You can retrieve a terrain at anytime
	///		\code 
	///			Terrain* pTerr =TerrainObjectManager::Get("loadedTerrain");
	///		\endcode
	/// The loaded Terrain can be set to the scene at any time using
	///		\code
	///
	///		SceneManager::GetCurrentScene()->SetTerrain("HillyTerrain");
	///
	///		\endcode
	//////////////////////////////////////////////////
	static TerrainModel* Get(const TerrainName& key) { return Instance().privGet(key); };

	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Loads a Terrain from file and associates it with key
	///
	///	Load(TerrainKey& key, const char* path) takes in a user created key in the form of a string and a path name that is also a string.
	///	The function loads the Terrain at the file location and associates it with the given string so it can be later loaded
	///	using given key. The base path from Load() is Assets/Terrains/. 
	///
	///	\param key a string that will be associated with the Terrain to be loaded, the key is used to retrieve the Terrain.
	///	\param  heightmapFile a string that is the path where the .tga file containing the Terrain to be loaded is found. 
	///		Root path is Assets/Terrains/ 
	///	\param len a float that repersents the length in world space of one side of the generated terrain
	/// \param maxheight float that repersents the maxiumum height of the terrain
	///	\param ytrans float that translates the terrain a certain number of spaces up or down in world space
	/// \param RepeatU	int that repersents the number of times the texture should be repeated in the u plane
	/// \param RepeatV int that repersents the number of times the texture should be repeated in the v plane
	/// \param tex std::string that is the name of the texture you want to use for the terrain. This texture should be previously loaded by the TextureManager
	///
	///	\par Example:
	///		
	///		\code
	///		void BlueBird::LoadAllResources() {
	///			TerrainObjectManager::Load("HillyTerrain", L"HMHills.tga", 10000, 1000, -1000, 1, 1, "grass");
	///			TerrainObjectManager::Load("FlatTerrain", L"HMFlat.tga", 5000, 1000, 0, 1, 1, "DanceFloor");
	///		}
	///		\endcode
	//////////////////////////////////////////////////
	static void Load(const TerrainName& key, LPCWSTR heightmapFile, const float& len, const float& maxheight, 
		const float& ytrans, const int& RepeatU, const int& RepeatV) { 
		Instance().privLoad(key, heightmapFile, len, maxheight, ytrans, RepeatU, RepeatV); 
	};

	static void Initialize(ID3D12GraphicsCommandList4* cmdList);
	static void Terminate();

private:

	static TerrainObjectManager* TerrainInstance;
	TerrainObjectManager();
	~TerrainObjectManager();
	TerrainObjectManager(const TerrainObjectManager&) = delete;
	TerrainObjectManager& operator=(const TerrainObjectManager&) = delete;

	static TerrainObjectManager& Instance()
	{
		if (!TerrainInstance)
			TerrainInstance = new TerrainObjectManager();
		return *TerrainInstance;


	}

	TerrainModel* privGet(const TerrainName& key);
	void privLoad(const TerrainName& key, LPCWSTR heightmapFile, const float& len, const float& maxheight,
		const float& ytrans, const int& RepeatU, const int& RepeatV);

	const wchar_t * defaultPath = L"../../../Assets/Textures/";
		
	TerrainModel* terrainArray[NumberOfTerrains];

	wchar_t* addDefaultPath(const wchar_t* path);

	ID3D12GraphicsCommandList4* loadCmdList;

	//char * charPath;
};
/// \}
#endif TerrainManager_H

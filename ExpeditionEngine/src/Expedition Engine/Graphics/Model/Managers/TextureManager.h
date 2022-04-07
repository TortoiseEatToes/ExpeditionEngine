#ifndef TextureManager_H
#define TextureManager_H

#include <Windows.h>
#include "../../../../Expedition Resources/TextureSettings.h"
#include <d3d12.h>
#include "../../../DX12App/d3dx12.h"

class Vect;
class Texture;

/////////////////////////////////
/// \ingroup ASSET
/// \{
////////////////////////////////////
/// Used to load and retrieve textures
////////////////////////////////////

class TextureManager
{
	friend class TextureManagerAttorney;

public:



	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Function used to retrieve a loaded Texture
	///
	///	Get(TextureKey& key) takes in a string and returns a pointer to the Texture that was loaded with that string as the
	///	key. If no Texture with given key exists, an error is thrown. This is a static function and can be 
	///	called with TextureManager::Get(key).
	///
	///	\param key the key of the Texture that is going to be returned
	///
	/// \par Example:
	///	If a Texture is loaded in Load Resources as such:
	///		\code
	///		
	///		TextureManager::Load("loadedTexture", "sampleTexture.tga");
	///		
	///		\endcode
	/// The loaded Texture can then be retrieved at any time like such:
	///		\code
	///
	///		Texture* tex = TextureManager::Get("loadedTexture");
	///
	///		\endcode
	//////////////////////////////////////////////////
	static Texture* Get(const TextureName& key) { return Instance().privGet(key); };

	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Loads a Texture from file and associates it with key
	///
	///	Load(TextureKey& key, const char* path) takes in a user created key in the form of a string and a path name that is also a string.
	///	The function loads the Texture at the file location and associates it with the given string so it can be later loaded
	///	using given key. The base path from Load() is Assets/Textures/. 
	///
	///	\param key a string that will be associated with the Texture to be loaded, the key is used to retrieve the Texture.
	///	\param path a string that is the path where the .tga file containing the Texture to be loaded is found. 
	///		Root path is Assets/Textures/ 
	///
	///	\par Example:
	///		
	///		\code
	///		void BlueBird::LoadAllResources() {
	///				TextureManager::Load("tankText", "grid.tga");
	///				TextureManager::Load("tankText2", "Duckweed.tga");
	///		}
	///		\endcode
	//////////////////////////////////////////////////
	static void Load(const TextureName& key, const wchar_t* path) { Instance().privLoad(key, path); };

	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Loads a Texture using RGB values and associates it with key
	///
	///	Load(TextureKey& key,const unsigned int& red, const unsigned int& green, const unsigned int& blue) takes in a user created key 
	/// in the form of a string and three unsigned ints (red, green, blue). The function loads a single pixel Texture with 
	///	the given RGB values and associates it with the given string so it can be later loaded using given key. 
	/// The base path from Load() is Assets/Textures/. 
	///
	///	\param key a string that will be associated with the Texture to be loaded, the key is used to retrieve the Texture.
	///	\param red an unsigned int that holds the red color value for the single pixel texture
	///	\param green an unsigned int that holds the green color value for the single pixel texture
	///	\param blue an unsigned int that holds the blue color value for the single pixel texture
	///
	///	\par Example:
	///		
	///		\code
	///		void BlueBird::LoadAllResources() {
	///				TextureManager::Load("Green", 0, 255, 0);
	///		}
	///		\endcode
	//////////////////////////////////////////////////
	//static void Load(TextureName& key, const unsigned int& red, const unsigned int& green, const unsigned int& blue) { Instance().privLoad(key, static_cast<unsigned char>(red), static_cast<unsigned char>(green), static_cast<unsigned char>(blue)); };
	
	/////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Loads a Texture using a Vect and associates it with key
	///
	///	Load(TextureKey& key,const Vect& col) takes in a user created key 
	/// in the form of a string and a Vect. The function loads a single pixel Texture with 
	///	using the x,y, and z values of the Vect as RGB values. It associates the texture with 
	/// the given string so it can be later loaded using given key. 
	/// The base path from Load() is Assets/Textures/. 
	///
	///	\param key a string that will be associated with the Texture to be loaded, the key is used to retrieve the Texture.
	///	\param col a Vect that repersents the single pixel color to be loaded. Use the Colors.h namespace for easy access to colors
	///
	///	\par Example:
	///		
	///		\code
	///		void BlueBird::LoadAllResources() {
	///				TextureManager::Load("Green", Colors::Green);
	///		}
	///		\endcode
	//////////////////////////////////////////////////
	//static void Load(TextureName& key, const Vector4F& col) { Instance().privLoad(key, col); };


	static CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPUTextureHandle(const TextureName& key);
	static CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUTextureHandle();

	static ID3D12DescriptorHeap* GetSRVHeap() {
		return Instance().g_SRVDescHeap;
	}

private:
	ID3D12DescriptorHeap* g_SRVDescHeap;

	static TextureManager* pInstance;
	TextureManager();
	~TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static TextureManager& Instance()
	{
		return *pInstance;
	}

	static void Initialize(ID3D12GraphicsCommandList4* cmdList);
	static void Terminate();

	Texture* privGet(const TextureName& key);
	void privLoad(const TextureName& key, const wchar_t* path);
	//void privLoad(TextureName& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue);
	//void privLoad(TextureName& key, const Vect& col);
	const wchar_t * defaultPath = L"../../../Assets/Textures/";
	Texture* textureArray[NumberOfTextures]{ nullptr };

	 wchar_t* addDefaultPath(const wchar_t* path);

	 ID3D12GraphicsCommandList4* loadCmdList;

	//char * charPath;
};
/// \}
#endif TextureManager_H

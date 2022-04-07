#ifndef ShaderManager_12_H
#define ShaderManager_12_H

#include "../../../Expedition Resources/ShaderSettings.h"
#include <d3d12.h>

class ShaderBase_12;

/////////////////////////////////
/// \ingroup ASSET
/// \{
////////////////////////////////////
/// Used to load and retrieve shaders
/// \note 
/// "constantColor" and "spriteShader" keys are used by preloaded shaders in the engine. attempting to use these keys will crash the engine.
////////////////////////////////////


class ShaderManager_12
{
	friend class ShaderManagerAttorney_12;
public:

	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Function used to retrieve a loaded ShaderObject
	///
	///	Get(ShaderKey& key) takes in a string and returns a pointer the ShaderObject that was loaded with that string as the
	///	key. If no shader with given key exists, an error is thrown. This is a static function and can be 
	///	called with ShaderManager::Get(key).
	///
	///	\param key the key of the shader that is going to be returned
	///
	/// \par Example:
	///	If a shader is loaded in Load Resources as such:
	///		\code
	///		
	///		ShaderManager::Load("loadedShader", "sampleShader");
	///		
	///		\endcode
	/// The loaded shader can then be retrieved at any time like such:
	///		\code
	///
	///		ShaderObject* shader = ShaderManager::Get("loadedShader");
	///
	///		\endcode
	//////////////////////////////////////////////////
	static ShaderBase_12* Get(const ShaderName& key) { return Instance().privGet(key); };

	//////////////////////////////////////////////////
	///	\ingroup ASSET
	/// \brief Loads a shader from file and associates it with key
	///
	///	Load(ShaderKey& key, const char* path) takes in a user created key in the form of a string and a path name that is also a string.
	///	The function loads the shader at the file location and associates it with the given string so it can be later loaded
	///	using given key. The base path from Load() is Assets/Shaders/. 
	///
	///	\param key a string that will be associated with the shader to be loaded, the key is used to retrieve the ShaderObject
	///	\param path a string that is the path where the .hlsl file containing the shader to be loaded is found. 
	///		Root path is Assets/Shaders/ 
	///
	///	\par Example:
	///		
	///		\code
	///		void BlueBird::LoadAllResources() {
	///			ShaderManager::Load("texture", "textureFlatRender");
	///			ShaderManager::Load("textureLight", "textureLightRender");
	///		}
	///		\endcode
	//////////////////////////////////////////////////
	static void Load(ShaderBase_12* shader) { Instance().privLoad(shader); };

private:

	static ShaderManager_12* shadeInstance;
	ShaderManager_12();
	~ShaderManager_12();
	ShaderManager_12(const ShaderManager_12&) = delete;
	ShaderManager_12& operator=(const ShaderManager_12&) = delete;

	static ShaderManager_12& Instance()
	{
		if (!shadeInstance) 
				shadeInstance = new ShaderManager_12();
		return *shadeInstance;

		
	}

	static void Initialize(ID3D12GraphicsCommandList4* cmdList, ID3D12GraphicsCommandList4* shadowCmdList);
	static void Terminate();


	ShaderBase_12* privGet(const ShaderName& key);
	void privLoad(ShaderBase_12* shader);

	ShaderBase_12** shaderArray;

};
/// \}
#endif ShaderManager_12_H
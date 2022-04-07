#ifndef ModelManager_H
#define ModelManager_H

//TODO: Asset Managers Terminate and Initialize need to be private!!

#include "../Model.h"
#include "../../../../Expedition Resources/ModelSettings.h"
#include <d3d12.h>
/////////////////////////////////
/// \ingroup ASSET
/// \{
////////////////////////////////////
/// Used to load and retrieve models
/// \note
/// "Sphere" and "Sprite" keys are used by BlueBire to load models used by the engine. Attempting to use these keys for other models will
/// crash the engine
////////////////////////////////////


class ModelManager
{
	friend class ModelManagerAttorney;
public:



	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Function used to retrieve a loaded Model
	///
	///	Get(ModelKey& key) takes in a string and returns a pointer to the Model that was loaded with that string as the
	///	key. If no model with given key exists, an error is thrown. This is a static function and can be 
	///	called with ModelManager::Get(key).
	///
	///	\param key the key of the model that is going to be returned
	///
	/// \par Example:
	///	If a model is loaded in Load Resources as such:
	///		\code
	///		
	///		ModelManager::Load("loadedModel", "sampleModel.azul");
	///		
	///		\endcode
	/// The loaded model can then be retrieved at any time like such:
	///		\code
	///
	///		Model* mod = ModelManager::Get("loadedModel");
	///
	///		\endcode
	//////////////////////////////////////////////////
	static Model* Get(const ModelName& key) { return Instance().privGet(key); };

	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Loads a model from file and associates it with key
	///
	///	Load(ModelKey& key, const char* path) takes in a user created key in the form of a string and a path name that is also a string.
	///	The function loads the model at the file location and associates it with the given string so it can be later loaded
	///	using given key. The base path from Load() is Assets/Models/. 
	///
	///	\param key a string that will be associated with the model to be loaded, the key is used to retrieve the model
	///	\param path a string that is the path where the .azul file containing the model to be loaded is found. 
	///		Root path is Assets/Models/ 
	///
	///	\par Example:
	///		
	///		\code
	///		void BlueBird::LoadAllResources() {
	///			ModelManager::Load("Axis", "Axis.azul");
	///			ModelManager::Load("Plane", "Plane.azul");
	///		}
	///		\endcode
	//////////////////////////////////////////////////
	static void Load(const ModelName& key, const char* path) { Instance().privLoad(key, path); };

	//////////////////////////////////////////////////
	/// \ingroup ASSET
	/// \brief Take a premade model and associates it with a key
	///
	///	Load(ModelKey& key,  Model::PreMadedeModels model) takes in a user created key in the form of a string and the enum of a premade model.
	///	The function loads the premade model and associates it with the given string so it can be later loaded
	///	using given key.
	///
	///	\param key a string that will be associated with the model to be loaded, the key is used to retrieve the model
	///	\param model the enum of the premade model to be loaded the options are:
	///		\code
	///			enum PreMadedeModels {
	///				UnitSquareXY,
	///				UnitBox_WF,
	///				UnitSphere
	///			};
	///		\endcode
	///	\par Example:
	///		
	///		\code
	///		void BlueBird::LoadAllResources() {
	///				ModelManager::Load("Sphere", Model::PreMadedeModels::UnitSphere);
	///		}
	///		\endcode
	//////////////////////////////////////////////////
	static void Load(const ModelName& key, Model::PreMadeModels model);

	static void Load(const ModelName& key, Model* model);
	static void LoadSprite(const ModelName& key, float x, float y);
	static void LoadFlatPlane(const ModelName& key, float x, float y);
	static void LoadSkyBox(const ModelName& key, float x, float y, float z);
	static void LoadBox(const ModelName& key, float width, float height, float depth);
private:

	static ModelManager* pInstance;
	ModelManager();
	~ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;

	static ModelManager& Instance()
	{
		return *pInstance;
	}

	static void Initialize(ID3D12GraphicsCommandList4* cmdList);
	static void Terminate();

	Model* privGet(const ModelName& key);
	void privLoad(const ModelName& key, const char* path);
	void privLoad(const ModelName& key, Model::PreMadeModels model);
	void privLoad(const ModelName& key, Model* model);

	const char* defaultPath = "../../../Assets/Models/";
	Model* modelArray[NumberOfModels]{ nullptr };

	char * addDefaultPath(const char* path);

	ID3D12GraphicsCommandList4* loadCmdList;
};
/// \}
#endif ModelManager_H


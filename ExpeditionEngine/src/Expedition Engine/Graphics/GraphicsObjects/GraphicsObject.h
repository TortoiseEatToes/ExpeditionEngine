#pragma once

/// Created by Emmaline Kelly, 2019
/// GraphicsObject is the base class for all types of GraphicObjects 

#include "../../../Expedition Resources/SceneSettings.h"
#include "../../Scenes/Commands/Registration Actions/RegistrationState.h"
#include "../../../Expedition Resources/TextureSettings.h"
#include "../../../Expedition Resources/ShaderSettings.h"
#include "GO_Data_Base.h"

class GO_Data_Manager;
class Texture;
class Matrix4F;
class Vector4F;
class Model;
class TerrainModel;

class GraphicsObject
{
	friend class GraphicsObjectAttorney;
private:

	/// <summary> 
	/// This function needs to be overridden in user made GraphicsObject. Used to set pModel to context, send world, and rendermesh 
	/// </summary>
	/// <example>Example 
	///		<code>
	///			pModel->SetToContext(pShader->GetContext());
	///			for (int i = 0; i lt pModel->GetMeshCount(); i++)
	///			{
	///				assert(MeshTextures[i]); //ONE OF YOUR MESH TEXTURES == NULLPTR
	///				pShader->SendWorldAndMaterial(World, MeshMaterials[i].Ambient, MeshMaterials[i].Diffuse, MeshMaterials[i].Specular);
	///				pShader->SetTextureResourceAndSampler(MeshTextures[i]);
	///				pModel->RenderMesh(pShader->GetContext(), i);
	///			}
	///		</code>
	/// </example>

	RegistrationState regState;
	PooledResourceIterator<GO_Data_Base> dataIterator;

	ShaderName shaderName;
	SceneName sceneParent;

	void StopDrawing();

	void StartDrawingChild(GO_Data_Manager* pGraphicsObjectDataManager) {};
	void StopDrawingChild(GO_Data_Manager* pGraphicsObjectDataManager) {};

	void RegisterColor(GO_Data_Manager* pGraphicsObjectDataManager);
	void RegisterColorLight(GO_Data_Manager* pGraphicsObjectDataManager);
	void RegisterTexture(GO_Data_Manager* pGraphicsObjectDataManager);
	void RegisterTextureLight(GO_Data_Manager* pGraphicsObjectDataManager);


	void DeregisterColor(GO_Data_Manager* pGraphicsObjectDataManager);
	void DeregisterColorLight(GO_Data_Manager* pGraphicsObjectDataManager);
	void DeregisterTexture(GO_Data_Manager* pGraphicsObjectDataManager);
	void DeregisterTextureLight(GO_Data_Manager* pGraphicsObjectDataManager);

public:
	GraphicsObject() = delete;
	GraphicsObject(const SceneName& sceneToStartIn, Model* mod, int numberOfInsts = 1);
	GraphicsObject(const SceneName& sceneToStartIn, TerrainModel* mod);
	GraphicsObject(const GraphicsObject&) = delete;				   // Copy constructor
	GraphicsObject(GraphicsObject&&) = default;                    // Move constructor
	GraphicsObject& operator=(const GraphicsObject&) & = default;  // Copy assignment operator
	GraphicsObject& operator=(GraphicsObject&&) & = default;       // Move assignment operator
	~GraphicsObject();		  							   // Destructor

	/// <summary> Starts drawing all instances of the GraphicsObject in the GraphicsObject's scene.</summary>
	void StartDrawingColor();
	void StartDrawingColorLight();
	void StartDrawingTexture();
	void StartDrawingTextureLight();

	/// <summary>Starts drawing all instances of the GraphicsObject in the GraphicsObject's scene.</summary>
	void StopDrawingColor();
	void StopDrawingColorLight();
	void StopDrawingTexture();
	void StopDrawingTextureLight();

	/// <summary> Set color of all instances of the GraphicsObject</summary>
	/// <param name="col">Vector4F new color of the GraphicsObject</param>
	void SetColor(const Vector4F& col);

	/// <summary> Set color for a specific instance of the GraphicsObject.</summary>
	/// <param name="col">Vector4F new color of the GraphicsObject</param>
	/// <param name="InstanceNum">Index of the instance that you want to access</param>
	void SetColorInstance(const Vector4F& col, int InstanceNum);

	/// <summary> Set the color of a specific mesh for a specific instance.</summary>
	/// <param name="col">Vector4F new color of the GraphicsObject</param>
	/// <param name="InstanceNum">Index of the instance that you want to access</param>
	/// <param name="meshnum">Index of the mesh you want to access</param>
	void SetColor(const Vector4F& col, int meshnum, int InstanceNum);

	/// <summary> Set the color of a specific mesh for all instances.</summary>
	/// <param name="col">Vector4F new color of the GraphicsObject</param>
	/// <param name="meshnum">Index of the mesh you want to access</param>
	void SetColorMesh(const Vector4F& col, int meshnum);

	void SetTexture(Texture* col);
	void SetTextureMesh(Texture* col, int meshnum);
	void SetTextureInstance(Texture* col, int instance);
	void SetTextureInstanceMesh(Texture* col, int instance, int meshnum);
	void SetTexture(const TextureName col);
	void SetTextureMesh(const TextureName col, int meshnum);
	void SetTextureInstance(const TextureName col, int instance);
	void SetTextureInstanceMesh(const TextureName col, int instance, int meshnum);
	void SetMaterial(const Vector4F& amb, const Vector4F& dif, const Vector4F& sp, const int InstanceID = 0);
	void SetMaterial(int meshnum, const Vector4F& amb, const Vector4F& dif, const Vector4F& sp, const int InstanceID = 0);

	void SetModel(Model* mod);
	void SetWorld(const Matrix4F& m, int InstanceID = 0);
	Matrix4F& GetWorldDraw(int id);
	Matrix4F& GetWorldUpdate(int id);

	Model* getModel();
	TerrainModel* GetTerrainModel();

	///<summary> Returns current Registration State of the Graphics Object. This indicats whether or not it is currently being drawn </summary>
	RegistrationState GetRegState() { return regState; }


};



#include "GraphicsObject.h"
#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"
#include "../Graphics Resources/GraphicsResourcesManager.h"

#include "../Model/Managers/TextureManager.h"
#include "../Model/Model.h"
#include "../Terrain/TerrainModelAttorney.h"

#include "../../../Expedition Resources/EngineSettings.h"
#include "../../../Expedition Resources/TextureSettings.h"

#include "../../GraphicsScene/GraphicsSceneManager.h"
#include "../../GraphicsScene/GraphicsSceneAttorney.h"



void GraphicsObject::RegisterColor(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->RegisterForDrawColor(dataIterator);
}

void GraphicsObject::RegisterColorLight(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->RegisterForDrawColorLight(dataIterator);
}

void GraphicsObject::RegisterTexture(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->RegisterForDrawTexture(dataIterator);
}

void GraphicsObject::RegisterTextureLight(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->RegisterForDrawTextureLight(dataIterator);
}

void GraphicsObject::DeregisterColor(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->DeregisterFromDrawColor(dataIterator);
}

void GraphicsObject::DeregisterColorLight(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->DeregisterFromDrawColorLight(dataIterator);
}

void GraphicsObject::DeregisterTexture(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->DeregisterFromDrawTexture(dataIterator);
}

void GraphicsObject::DeregisterTextureLight(GO_Data_Manager* pGraphicsObjectDataManager)
{
	pGraphicsObjectDataManager->DeregisterFromDrawTextureLight(dataIterator);
}

GraphicsObject::GraphicsObject(const SceneName& sceneToStartIn, Model* mod, int numberOfInsts)
{
	sceneParent = sceneToStartIn; //set parent scene with user value
	regState = RegistrationState::CURRENTLY_DEREGISTERED; // set registration state

	GraphicsSceneAttorney::GraphicsObjectChildControl::GetGraphicsObjectDataManager(GraphicsSceneManager::GetScene(sceneToStartIn)).Acquire_12(dataIterator, mod, numberOfInsts);
}

GraphicsObject::GraphicsObject(const SceneName& sceneToStartIn, TerrainModel* mod)
{
	sceneParent = sceneToStartIn; //set parent scene with user value
	regState = RegistrationState::CURRENTLY_DEREGISTERED; // set registration state

	GraphicsSceneAttorney::GraphicsObjectChildControl::GetGraphicsObjectDataManager(GraphicsSceneManager::GetScene(sceneToStartIn)).Acquire_12(dataIterator, mod);
}

GraphicsObject::~GraphicsObject()
{
	if (regState == RegistrationState::CURRENTLY_REGISTERED || regState == RegistrationState::PENDING_REGISTRATION) 
	{
		StopDrawing();
	}

	GraphicsSceneAttorney::GraphicsObjectChildControl::GetGraphicsObjectDataManager(GraphicsSceneManager::GetScene(sceneParent)).Release_12(dataIterator);

	sceneParent = static_cast<SceneName>(-1);
	regState = static_cast<RegistrationState>(-1);
}


void GraphicsObject::SetTexture(Texture* tex)
{
	for (int i = 0; i < (dataIterator.GetCurrentObject().pModel->GetMeshCount()); i++)
	{
		for (int j = 0; j < dataIterator.GetCurrentObject().numberOfInstances; j++) {
			dataIterator.GetCurrentObject().MeshTextures[i][j].GetCurrentObject().SetUpdate(tex);
		}
	}
}

void GraphicsObject::SetTextureMesh(Texture* tex, int meshnum)
{
	assert(dataIterator.GetCurrentObject().pModel->ValidMeshNum(meshnum));

	for (int j = 0; j < dataIterator.GetCurrentObject().numberOfInstances; j++) {
		dataIterator.GetCurrentObject().MeshTextures[meshnum][j].GetCurrentObject().SetUpdate(tex);
	}
}

void GraphicsObject::SetTextureInstance(Texture* tex, int instance)
{
	for (int i = 0; i < (dataIterator.GetCurrentObject().pModel->GetMeshCount()); i++)
	{
		dataIterator.GetCurrentObject().MeshTextures[i][instance].GetCurrentObject().SetUpdate(tex);
	}
}

void GraphicsObject::SetTextureInstanceMesh(Texture* tex, int instance, int meshnum)
{
	dataIterator.GetCurrentObject().MeshTextures[meshnum][instance].GetCurrentObject().SetUpdate(tex);
}

void GraphicsObject::SetTexture(const TextureName col)
{
	SetTexture(TextureManager::Get(col));
}

void GraphicsObject::SetTextureMesh(const TextureName col, int meshnum)
{
	SetTextureMesh(TextureManager::Get(col), meshnum);
}

void GraphicsObject::SetTextureInstance(const TextureName col, int instance)
{
	SetTextureInstance(TextureManager::Get(col), instance);
}

void GraphicsObject::SetTextureInstanceMesh(const TextureName col, int instance, int meshnum)
{
	SetTextureInstanceMesh(TextureManager::Get(col), instance, meshnum);
}

void GraphicsObject::SetMaterial(const Vector4F& amb, const Vector4F& dif, const Vector4F& sp, const int InstanceID)
{
	assert(InstanceID < dataIterator.GetCurrentObject().numberOfInstances);
	for (int i = 0; i < dataIterator.GetCurrentObject().pModel->GetMeshCount(); i++) {
		dataIterator.GetCurrentObject().pMeshMaterials[i][InstanceID]->Diffuse().SetUpdate(dif);
		dataIterator.GetCurrentObject().pMeshMaterials[i][InstanceID]->Ambient().SetUpdate(amb);
		dataIterator.GetCurrentObject().pMeshMaterials[i][InstanceID]->Specular().SetUpdate(sp);
	}
}

void GraphicsObject::SetMaterial(int meshnum, const Vector4F& amb, const Vector4F& dif, const Vector4F& sp, const int InstanceID)
{
	assert(dataIterator.GetCurrentObject().pModel->ValidMeshNum(meshnum));
	dataIterator.GetCurrentObject().pMeshMaterials[meshnum][InstanceID]->Ambient().SetUpdate(amb);
	dataIterator.GetCurrentObject().pMeshMaterials[meshnum][InstanceID]->Diffuse().SetUpdate(dif);
	dataIterator.GetCurrentObject().pMeshMaterials[meshnum][InstanceID]->Specular().SetUpdate(sp);
}

void GraphicsObject::SetModel(Model* mod)
{
	dataIterator.GetCurrentObject().pModel = mod;
}

void GraphicsObject::SetWorld(const Matrix4F& m, int instanceID)
{
	dataIterator.GetCurrentObject().pWorld[instanceID].GetCurrentObject().SetUpdate(m);
}

Matrix4F& GraphicsObject::GetWorldDraw(int instanceID)
{
	return dataIterator.GetCurrentObject().pWorld[instanceID].GetCurrentObject().GetDraw();
}

Matrix4F& GraphicsObject::GetWorldUpdate(int instanceID)
{
	return dataIterator.GetCurrentObject().pWorld[instanceID].GetCurrentObject().GetUpdate();
}

Model* GraphicsObject::getModel()
{
	return dataIterator.GetCurrentObject().pModel;
}

TerrainModel* GraphicsObject::GetTerrainModel()
{
	return dataIterator.GetCurrentObject().terrainModel;
}

void GraphicsObject::StartDrawingColor()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED || regState == RegistrationState::PENDING_DEREGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StartDrawingColor(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_REGISTRATION; // set new reg state
}

void GraphicsObject::StartDrawingColorLight()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED || regState == RegistrationState::PENDING_DEREGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StartDrawingColorLight(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_REGISTRATION; // set new reg state
}

void GraphicsObject::StartDrawingTexture()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED || regState == RegistrationState::PENDING_DEREGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StartDrawingTexture(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_REGISTRATION; // set new reg state
}

void GraphicsObject::StartDrawingTextureLight()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED || regState == RegistrationState::PENDING_DEREGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StartDrawingTextureLight(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_REGISTRATION; // set new reg state
}

void GraphicsObject::StopDrawingColor()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED || regState == RegistrationState::PENDING_REGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StopDrawingColor(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_DEREGISTRATION; // set new reg state
}

void GraphicsObject::StopDrawingColorLight()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED || regState == RegistrationState::PENDING_REGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StopDrawingColorLight(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_DEREGISTRATION; // set new reg state
}

void GraphicsObject::StopDrawingTexture()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED || regState == RegistrationState::PENDING_REGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StopDrawingTexture(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_DEREGISTRATION; // set new reg state
}

void GraphicsObject::StopDrawingTextureLight()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED || regState == RegistrationState::PENDING_REGISTRATION);  // assert registration state for debugging
	GraphicsSceneManagerAttorney::GraphicsObjectControl::StopDrawingTextureLight(sceneParent, this); //remove from draw list through scene attorney
	regState = RegistrationState::PENDING_DEREGISTRATION; // set new reg state
}

void GraphicsObject::StopDrawing()
{
	//TODO

	//please ignore the switch, Sara, it's only called on destruction :(

	switch (shaderName)
	{
	case(ShaderName::Color):
		StopDrawingColor();
		break;
	case(ShaderName::ColorLight):
		StopDrawingColorLight();
		break;
	case(ShaderName::TextureLight):
		StopDrawingTextureLight();
		break;
	case(ShaderName::TextureShader):
		StopDrawingTexture();
		break;
	default:
		break;
	}
}

void GraphicsObject::SetColor(const Vector4F& col)
{
	for (int i = 0; i < dataIterator.GetCurrentObject().meshCount; i++)
	{
		for (int j = 0; j < dataIterator.GetCurrentObject().numberOfInstances; j++)
		{
			dataIterator.GetCurrentObject().pMeshMaterials[i][j]->Ambient().SetUpdate(col);
		}
	}
}

void GraphicsObject::SetColorInstance(const Vector4F& col, int InstanceNum)
{

	for (int i = 0; i < dataIterator.GetCurrentObject().pModel->GetMeshCount(); i++)
	{
		dataIterator.GetCurrentObject().pMeshMaterials[i][InstanceNum]->Ambient().SetUpdate(col);
	}
}

void GraphicsObject::SetColorMesh(const Vector4F& col, int meshnum)
{
	for (int i = 0; i < dataIterator.GetCurrentObject().numberOfInstances; ++i)
	{
		dataIterator.GetCurrentObject().pMeshMaterials[meshnum][i]->Ambient().SetUpdate(col);
	}

}

void GraphicsObject::SetColor(const Vector4F& col, int meshnum, int InstanceNum)
{
	assert(dataIterator.GetCurrentObject().pModel->ValidMeshNum(meshnum));
	dataIterator.GetCurrentObject().pMeshMaterials[meshnum][InstanceNum]->Ambient().SetUpdate(col);
}


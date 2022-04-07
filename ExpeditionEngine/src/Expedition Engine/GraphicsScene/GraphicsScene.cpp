#include "GraphicsScene.h"

#include "Commands/GraphicsSceneCommand.h"
#include "../Graphics/GraphicsObjects/GraphicsObjectAttorney.h"
#include "../Engine/ExpeditionEngineAttorney.h"
#include "../Camera/Camera.h"
#include "../../Expedition Resources/LayerSettings.h"


#include "../Scenes/SceneManagerAttorney.h"
#include "../Camera/CameraData.h"

GraphicsScene::GraphicsScene()
	: graphicsResourcesManager() 
{
	graphicsObjectDataManager.Initialize(&graphicsResourcesManager);
}

GraphicsScene::~GraphicsScene() {

	while (commandQueue.GetSize() > 0)
	{
		pTempCommand = commandQueue.Pop();
		pTempCommand->RecycleCommand();
	}
}

void GraphicsScene::SceneInitialize(const SceneName& sceneName)
{
	LightMgr.SceneInitialize(graphicsResourcesManager, sceneName);

	ProcessCommands();
}

void GraphicsScene::SceneStart()
{
	LightMgr.SceneStart(graphicsResourcesManager);
}

void GraphicsScene::SceneStop()
{
	LightMgr.SceneStop(graphicsResourcesManager);

	ProcessCommands();
}

void GraphicsScene::SceneSanitize()
{
	LightMgr.SceneSanitize(graphicsResourcesManager);

	ProcessCommands();
}


void GraphicsScene::Synchronize()
{
	graphicsResourcesManager.Synchronize();
}

void GraphicsScene::ProcessCommands()
{
	while (commandQueue.GetSize() > 0)
	{
		pTempCommand = commandQueue.Pop();
		pTempCommand->Execute(this);
		pTempCommand->RecycleCommand();
	}
}

void GraphicsScene::Render() 
{
	graphicsObjectDataManager.Render_12(DXApp_12::GetCommandList(), DXApp_12::GetShadowCommandList());
}

void GraphicsScene::RenderParticles()
{
	ParticleManagerAttorney::GraphicsSceneControl::ComputeAndRenderDX12(particleManager, SceneManagerAttorney::GraphicsControl::GetCurrentPerspectiveCameraData().GetPosition());
}


void GraphicsScene::InsertCommand(GraphicsSceneCommand* pCommand) 
{
	commandQueue.Push(pCommand);
}

//void GraphicsScene::RegisterGraphicsObject(GraphicsObject* pGO) 
//{
//	GraphicsObjectAttorney::GraphicsSceneControl::RegisterGraphicsObject(pGO, &graphicsObjectDataManager);
//	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_REGISTERED, pGO);
//
//	//renderList[pGO->GetShader()].PushFront(*pGO);
//	//renderList[pGO->GetShader()].SetFront(listIterator);
//	//
//	//GraphicsObjectAttorney::DeleteRef::SetDeleteRef(listIterator, pGO);
//	//GraphicsObjectAttorney::DeleteRef::SetRegistrationState(RegistrationState::CURRENTLY_REGISTERED, pGO);
//
//	//renderList[pGO->GetShader()->getShaderName()].push_front(pGO);
//	//
//	//listIterator = renderList[pGO->GetShader()->getShaderName()].begin();
//	//
//	//GraphicObjectAttorney::DeleteRef::SetDeleteRef(listIterator, pGO);
//	//GraphicObjectAttorney::DeleteRef::SetRegistrationState(RegistrationState::CURRENTLY_REGISTERED, pGO);
//}
//
//void GraphicsScene::DeregisterGraphicsObject(GraphicsObject* pGO) 
//{
//	GraphicsObjectAttorney::GraphicsSceneControl::DeregisterGraphicsObject(pGO, &graphicsObjectDataManager);
//	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED, pGO);
//
//	//listIterator = GraphicsObjectAttorney::DeleteRef::GetDeleteRef(pGO);
//	//renderList[pGO->GetShader()].Remove(listIterator);
//	//GraphicsObjectAttorney::DeleteRef::SetRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED, pGO);
//
//	//listIterator = GraphicObjectAttorney::DeleteRef::GetDeleteRef(pGO);
//	//renderList[pGO->GetShader()->getShaderName()].erase(listIterator);
//	//GraphicObjectAttorney::DeleteRef::SetRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED, pGO);
//}

void GraphicsScene::RegisterGraphicsObjectColor(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::RegisterColor(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_REGISTERED, pGO);
}

void GraphicsScene::DeregisterGraphicsObjectColor(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::DeregisterColor(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED, pGO);
}

void GraphicsScene::RegisterGraphicsObjectColorLight(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::RegisterColorLight(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_REGISTERED, pGO);
}

void GraphicsScene::DeregisterGraphicsObjectColorLight(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::DeregisterColorLight(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED, pGO);
}

void GraphicsScene::RegisterGraphicsObjectTexture(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::RegisterTexture(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_REGISTERED, pGO);
}

void GraphicsScene::DeregisterGraphicsObjectTexture(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::DeregisterTexture(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED, pGO);
}

void GraphicsScene::RegisterGraphicsObjectTextureLight(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::RegisterTextureLight(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_REGISTERED, pGO);
}

void GraphicsScene::DeregisterGraphicsObjectTextureLight(GraphicsObject* pGO)
{
	GraphicsObjectAttorney::GraphicsSceneControl::DeregisterTextureLight(pGO, &graphicsObjectDataManager);
	GraphicsObjectAttorney::GraphicsSceneControl::SetRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED, pGO);
}

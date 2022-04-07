#include "GO_Data_Manager.h"

#include "../../../DX12App/DXApp/DXApp_12.h"
#include "../../../DX12App/FrameResources/FrameResourceInstanced.h"
#include "../../../GraphicsScene/GraphicsSceneManager.h"
#include "../../../Scenes/SceneManagerAttorney.h"

GO_Data_Manager::GO_Data_Manager()
	:dataPool(NumberOfGraphicsObjects)
{
}

GO_Data_Manager::~GO_Data_Manager()
{

}

void GO_Data_Manager::Render_12(ID3D12GraphicsCommandList4* cmdList, ID3D12GraphicsCommandList4* shadowCmdList)
{

	colorManager.PrepareGOsForRender(shadowCmdList);
	colorLightManager.PrepareGOsForRender(shadowCmdList);
	textureManager.PrepareGOsForRender(shadowCmdList);
	textureLightManager.PrepareGOsForRender(shadowCmdList);

	DXApp_12::PrepareToRenderShadows();

	Data_Shadow data;

	List<Shadow*>* list = GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->GetShadowMgr()->GetList();

	List<Shadow*>::Iterator it;
	list->SetFront(it);

	while (!it.IsOutOfNodes()) 
	{
		DXApp_12::PrepareShadow(it.GetCurrentObject());

		data.View = it.GetCurrentObject()->GetCamera()->GetViewMatrix();
		data.Projection = it.GetCurrentObject()->GetCamera()->GetProjMatrix();

		DXApp_12::GetFrameResourceInstanced()->SendShadowDataToGPU(data, DXApp_12::GetShadowCommandList(), it.GetCurrentObject()->offset);
		colorManager.Render_12(shadowCmdList);
		colorLightManager.Render_12(shadowCmdList);
		textureManager.Render(shadowCmdList);
		textureLightManager.Render_12(shadowCmdList);

		DXApp_12::CloseShadow(it.GetCurrentObject());

		it.GetNext(it);
	}

	DXApp_12::FinishRenderingShadows();

	DXApp_12::GetFrameResourceInstanced()->UpdatePerFrameData(SceneManagerAttorney::GraphicsControl::GetCurrentPerspectiveCameraData(), cmdList);
	
	DXApp_12::SetColorRootSig();
	colorManager.SendShader(cmdList);
	colorManager.Render_12(cmdList);
	
	DXApp_12::SetColorShadowRootSig();
	colorLightManager.SendShader(cmdList);
	colorLightManager.Render_12(cmdList);
	
	DXApp_12::SetTextureRootSig();
	textureManager.SendShader(cmdList);
	textureManager.Render(cmdList);
	textureLightManager.SendShader(cmdList);
	textureLightManager.Render_12(cmdList);

}




void GO_Data_Manager::Acquire_12(PooledResourceIterator<GO_Data_Base>& iterator, Model* pModel, int numberOfInsts)
{
	dataPool.AcquireResource(iterator);

	GO_Data_BaseAttorney::ManagerControl::Initialize_12(iterator.GetCurrentObject(), pGraphicsResourcesManager, pModel, numberOfInsts);
}

void GO_Data_Manager::Acquire_12(PooledResourceIterator<GO_Data_Base>& iterator, TerrainModel* pTerrainModel)
{
	dataPool.AcquireResource(iterator);

	GO_Data_BaseAttorney::ManagerControl::Initialize_12(iterator.GetCurrentObject(), pGraphicsResourcesManager, pTerrainModel);
}

void GO_Data_Manager::Release_12(PooledResourceIterator<GO_Data_Base>& iterator)
{
	GO_Data_BaseAttorney::ManagerControl::Sanitize_12(iterator.GetCurrentObject(), pGraphicsResourcesManager);
	dataPool.ReleaseResource(iterator);
}

void GO_Data_Manager::RegisterForDrawColor(PooledResourceIterator<GO_Data_Base>& iterator)
{
	colorManager.RegisterForDraw(iterator);
}

void GO_Data_Manager::RegisterForDrawColorLight(PooledResourceIterator<GO_Data_Base>& iterator)
{
	colorLightManager.RegisterForDraw(iterator);
}


void GO_Data_Manager::RegisterForDrawTexture(PooledResourceIterator<GO_Data_Base>& iterator)
{
	textureManager.RegisterForDraw(iterator);
}

void GO_Data_Manager::RegisterForDrawTextureLight(PooledResourceIterator<GO_Data_Base>& iterator)
{
	textureLightManager.RegisterForDraw(iterator);
}

void GO_Data_Manager::DeregisterFromDrawColor(PooledResourceIterator<GO_Data_Base>& iterator)
{
	colorManager.DeregisterFromDraw(iterator);
}

void GO_Data_Manager::DeregisterFromDrawColorLight(PooledResourceIterator<GO_Data_Base>& iterator)
{
	colorLightManager.DeregisterFromDraw(iterator);
}

void GO_Data_Manager::DeregisterFromDrawTexture(PooledResourceIterator<GO_Data_Base>& iterator)
{
	textureManager.DeregisterFromDraw(iterator);
}

void GO_Data_Manager::DeregisterFromDrawTextureLight(PooledResourceIterator<GO_Data_Base>& iterator)
{
	textureLightManager.DeregisterFromDraw(iterator);
}

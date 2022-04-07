#include "GO_Data_ColorLight_Manager.h"

#include "../../../../Expedition Resources/GraphicsResourcesSettings.h"

#include "../../../DX12App/Shaders/ShaderManager_12.h"
#include "../../../DX12App/Shaders/ShaderColorLight_12.h"
#include "../GO_Data_BaseAttorney.h"

GO_Data_ColorLight_Manager::GO_Data_ColorLight_Manager()
	//: dataPool(NumberOfGraphicsObjectsColorLight)
{
}

void GO_Data_ColorLight_Manager::RegisterForDraw(PooledResourceIterator<GO_Data_Base>& iterator)
{
	activeData.PushBack(iterator);
}

void GO_Data_ColorLight_Manager::DeregisterFromDraw(PooledResourceIterator<GO_Data_Base>& iterator)
{
	activeData.Remove(iterator);
}


//void GO_Data_ColorLight_Manager::Acquire_12(PooledResourceIterator<GO_Data_ColorLight>& iterator, GraphicsResourcesManager* pGraphicsResourcesManager, Model* pModel, int numberOfInsts)
//{
//	dataPool.AcquireResource(iterator);
//	GO_Data_ColorLightAttorney::ManagerControl::Initialize_12(iterator.GetCurrentObject(),  pGraphicsResourcesManager, pModel, numberOfInsts);
//}
//
//void GO_Data_ColorLight_Manager::Acquire_12(PooledResourceIterator<GO_Data_ColorLight>& iterator, GraphicsResourcesManager* pGraphicsResourcesManager, TerrainModel* pTerrainModel)
//{
//	dataPool.AcquireResource(iterator);
//	GO_Data_ColorLightAttorney::ManagerControl::Initialize_12(iterator.GetCurrentObject(), pGraphicsResourcesManager, pTerrainModel);
//}
//
//void GO_Data_ColorLight_Manager::Release_12(PooledResourceIterator<GO_Data_ColorLight>& iterator, GraphicsResourcesManager*& pGraphicsResourcesManager)
//{
//	GO_Data_ColorLightAttorney::ManagerControl::Sanitize_12(iterator.GetCurrentObject(), pGraphicsResourcesManager);
//	dataPool.ReleaseResource(iterator);
//}

void GO_Data_ColorLight_Manager::PrepareGOsForRender(ID3D12GraphicsCommandList4* cmdList)
{
	activeData.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		GO_Data_BaseAttorney::ManagerControl::PrepareForRender(currentIterator.GetCurrentObject(), cmdList);
		++currentIterator;
	}
}

void GO_Data_ColorLight_Manager::SendShader(ID3D12GraphicsCommandList4* cmdList)
{
	ShaderManager_12::Get(ShaderName::ColorLight)->PrepareToRender(cmdList);
}

void GO_Data_ColorLight_Manager::Render_12(ID3D12GraphicsCommandList4* cmdList)
{
	activeData.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		GO_Data_BaseAttorney::ManagerControl::Render_12(currentIterator.GetCurrentObject(), cmdList);
		++currentIterator;
	}
}
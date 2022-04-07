#include "GO_Data_Color_Manager.h"

#include "../../../../Expedition Resources/GraphicsResourcesSettings.h"

#include "../../../DX12App/Shaders/ShaderManager_12.h"
#include "../../../DX12App/Shaders/ShaderColor_12.h"

#include "../GO_Data_BaseAttorney.h"

GO_Data_Color_Manager::GO_Data_Color_Manager()
	//:dataPool(NumberOfGraphicsObjectsColor)
{
}

void GO_Data_Color_Manager::RegisterForDraw(PooledResourceIterator<GO_Data_Base>& iterator)
{
	activeData.PushBack(iterator);
}

void GO_Data_Color_Manager::DeregisterFromDraw(PooledResourceIterator<GO_Data_Base>& iterator)
{
	activeData.Remove(iterator);
}


//void GO_Data_Color_Manager::Acquire_12(PooledResourceIterator<GO_Data_Color>& iterator, GraphicsResourcesManager* pGraphicsResourcesManager, Model* pModel, int numberOfInsts)
//{
//	dataPool.AcquireResource(iterator);
//
//	GO_Data_ColorAttorney::ManagerControl::Initialize_12(iterator.GetCurrentObject(), pGraphicsResourcesManager, pModel, numberOfInsts);
//}
//
//
//void GO_Data_Color_Manager::Release_12(PooledResourceIterator<GO_Data_Color>& iterator, GraphicsResourcesManager*& pGraphicsResourcesManager)
//{
//	GO_Data_ColorAttorney::ManagerControl::Sanitize_12(iterator.GetCurrentObject(), pGraphicsResourcesManager);
//	dataPool.ReleaseResource(iterator);
//}

void GO_Data_Color_Manager::PrepareGOsForRender(ID3D12GraphicsCommandList4* cmdList)
{
	activeData.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		GO_Data_BaseAttorney::ManagerControl::PrepareForRender(currentIterator.GetCurrentObject(), cmdList);
		++currentIterator;
	}
}

void GO_Data_Color_Manager::SendShader(ID3D12GraphicsCommandList4* cmdList)
{
	ShaderManager_12::Get(ShaderName::Color)->PrepareToRender(cmdList);
}

void GO_Data_Color_Manager::Render_12(ID3D12GraphicsCommandList4* cmdList)
{
	activeData.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		GO_Data_BaseAttorney::ManagerControl::Render_12(currentIterator.GetCurrentObject(), cmdList);
		++currentIterator;
	}
}

#include "GO_Data_Texture_Manager.h"

#include "../../../../Expedition Resources/GraphicsResourcesSettings.h"


#include "../../../DX12App/Shaders/ShaderManager_12.h"
#include "../../../DX12App/Shaders/ShaderTexture_12.h"

GO_Data_Texture_Manager::GO_Data_Texture_Manager()
	//:dataPool(NumberOfGraphicsObjectsTexture)
{
}

void GO_Data_Texture_Manager::RegisterForDraw(PooledResourceIterator<GO_Data_Base>& iterator)
{
	activeData.PushBack(iterator);
}

void GO_Data_Texture_Manager::DeregisterFromDraw(PooledResourceIterator<GO_Data_Base>& iterator)
{
	activeData.Remove(iterator);
}

//void GO_Data_Texture_Manager::Acquire(PooledResourceIterator<GO_Data_Texture>& iterator, GraphicsResourcesManager* pGraphicsResourcesManager, Model* pModel, int numberOfInsts)
//{
//	dataPool.AcquireResource(iterator);
//	GO_Data_TextureAttorney::ManagerControl::Initialize(iterator.GetCurrentObject(), pGraphicsResourcesManager, pModel, numberOfInsts);
//}
//
//void GO_Data_Texture_Manager::Release(PooledResourceIterator<GO_Data_Texture>& iterator, GraphicsResourcesManager*& pGraphicsResourcesManager)
//{
//	GO_Data_TextureAttorney::ManagerControl::Sanitize(iterator.GetCurrentObject(), pGraphicsResourcesManager);
//	dataPool.ReleaseResource(iterator);
//}

void GO_Data_Texture_Manager::PrepareGOsForRender(ID3D12GraphicsCommandList4* cmdList)
{
	activeData.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		GO_Data_BaseAttorney::ManagerControl::PrepareForRender(currentIterator.GetCurrentObject(), cmdList);
		++currentIterator;
	}
}

void GO_Data_Texture_Manager::SendShader(ID3D12GraphicsCommandList4* cmdList)
{
	ShaderManager_12::Get(ShaderName::TextureShader)->PrepareToRender(cmdList);
}

void GO_Data_Texture_Manager::Render(ID3D12GraphicsCommandList4* cmdList)
{
	activeData.SetFront(currentIterator);
	while (!currentIterator.IsOutOfNodes())
	{
		GO_Data_BaseAttorney::ManagerControl::Render_12(currentIterator.GetCurrentObject(), cmdList);
		++currentIterator;
	}
}
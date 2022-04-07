#pragma once

#include "../../../Containers/ResourcePool.h"
#include "../../../Containers/List_PooledResource.h"

#include "../GO_Data_BaseAttorney.h"

class GO_Data_Texture_Manager
{
public:
	GO_Data_Texture_Manager();
	GO_Data_Texture_Manager(const GO_Data_Texture_Manager&) = delete;
	GO_Data_Texture_Manager& operator= (const GO_Data_Texture_Manager&) = delete;
	~GO_Data_Texture_Manager() = default;

	void RegisterForDraw(PooledResourceIterator<GO_Data_Base>& iterator);
	void DeregisterFromDraw(PooledResourceIterator<GO_Data_Base>& iterator);
	
	//void Acquire(PooledResourceIterator<GO_Data_Texture>& iterator, GraphicsResourcesManager* pGraphicsResourcesManager, Model* pModel, int numberOfInsts);
	//void Release(PooledResourceIterator<GO_Data_Texture>& iterator, GraphicsResourcesManager*& pGraphicsResourcesManager);

	void PrepareGOsForRender(ID3D12GraphicsCommandList4* cmdList);
	void SendShader(ID3D12GraphicsCommandList4* cmdList);
	void Render(ID3D12GraphicsCommandList4* cmdList);

private:
	//ResourcePool<GO_Data_Texture> dataPool;
	List_PooledResource<GO_Data_Base> activeData;
	PooledResourceIterator<GO_Data_Base> currentIterator;
};
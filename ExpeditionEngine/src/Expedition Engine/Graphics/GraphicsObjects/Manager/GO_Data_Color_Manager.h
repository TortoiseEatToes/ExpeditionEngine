#pragma once

#include "../../../Containers/ResourcePool.h"
#include "../../../Containers/List_PooledResource.h"

#include "../GO_Data_Base.h"

class GO_Data_Color_Manager
{
public:
	GO_Data_Color_Manager();
	GO_Data_Color_Manager(const GO_Data_Color_Manager&) = delete;
	GO_Data_Color_Manager& operator= (const GO_Data_Color_Manager&) = delete;
	~GO_Data_Color_Manager() = default;

	void RegisterForDraw(PooledResourceIterator<GO_Data_Base>& iterator);
	void DeregisterFromDraw(PooledResourceIterator<GO_Data_Base>& iterator);

	//void Acquire_12(PooledResourceIterator<GO_Data_Color>& iterator, GraphicsResourcesManager* pGraphicsResourcesManager, Model* pModel, int numberOfInsts);
	//void Release_12(PooledResourceIterator<GO_Data_Color>& iterator, GraphicsResourcesManager*& pGraphicsResourcesManager);

	void PrepareGOsForRender(ID3D12GraphicsCommandList4* cmdList);
	void SendShader(ID3D12GraphicsCommandList4* cmdList);
	void Render_12(ID3D12GraphicsCommandList4* cmdList);

private:
	//ResourcePool<GO_Data_Color> dataPool;
	List_PooledResource<GO_Data_Base> activeData;
	PooledResourceIterator<GO_Data_Base> currentIterator;
};
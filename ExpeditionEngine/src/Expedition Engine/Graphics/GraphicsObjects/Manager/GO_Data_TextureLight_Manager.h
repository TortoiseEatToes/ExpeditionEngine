#pragma once

#include "../../../Containers/ResourcePool.h"
#include "../../../Containers/List_PooledResource.h"

#include "../GO_Data_BaseAttorney.h"

class GO_Data_TextureLight_Manager
{
public:
	GO_Data_TextureLight_Manager();
	GO_Data_TextureLight_Manager(const GO_Data_TextureLight_Manager&) = delete;
	GO_Data_TextureLight_Manager& operator= (const GO_Data_TextureLight_Manager&) = delete;
	~GO_Data_TextureLight_Manager() = default;

	void RegisterForDraw(PooledResourceIterator<GO_Data_Base>& iterator);
	void DeregisterFromDraw(PooledResourceIterator<GO_Data_Base>& iterator);

	void PrepareGOsForRender(ID3D12GraphicsCommandList4* cmdList);
	void SendShader(ID3D12GraphicsCommandList4* cmdList);
	void Render_12(ID3D12GraphicsCommandList4* cmdList);

private:
	List_PooledResource<GO_Data_Base> activeData;
	PooledResourceIterator<GO_Data_Base> currentIterator;
};
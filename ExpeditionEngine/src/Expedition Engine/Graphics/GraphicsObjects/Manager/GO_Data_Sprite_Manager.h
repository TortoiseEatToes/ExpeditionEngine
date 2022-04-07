//#pragma once
//
//#include "../../../Containers/ResourcePool.h"
//#include "../../../Containers/List_PooledResource.h"
//
//#include "../GO_Data_SpriteAttorney.h"
//
//class GO_Data_Sprite_Manager
//{
//public:
//	GO_Data_Sprite_Manager();
//	GO_Data_Sprite_Manager(const GO_Data_Sprite_Manager&) = delete;
//	GO_Data_Sprite_Manager& operator= (const GO_Data_Sprite_Manager&) = delete;
//	~GO_Data_Sprite_Manager() = default;
//
//	void RegisterForDraw(PooledResourceIterator<GO_Data_Sprite>& iterator);
//	void DeregisterFromDraw(PooledResourceIterator<GO_Data_Sprite>& iterator);
//
//	void Acquire(PooledResourceIterator<GO_Data_Sprite>& iterator, ID3D11Device* pDXDevice, GraphicsResourcesManager* pGraphicsResourcesManager, const SceneName& sceneToExistIn, SpriteData* pSprite, int numberOfInsts);
//	void Acquire(PooledResourceIterator<GO_Data_Sprite>& iterator, ID3D11Device* pDXDevice, GraphicsResourcesManager* pGraphicsResourcesManager, const SceneName& sceneToExistIn, Image* pImage, Rect* pRect, int numberOfInsts);
//
//	void Release(PooledResourceIterator<GO_Data_Sprite>& iterator, GraphicsResourcesManager*& pGraphicsResourcesManager);
//
//	void Render(ID3D11Device*& pDXDevice, ID3D11DeviceContext*& pDXContext);
//
//private:
//	ResourcePool<GO_Data_Sprite> dataPool;
//	List_PooledResource<GO_Data_Sprite> activeData;
//	PooledResourceIterator<GO_Data_Sprite> currentIterator;
//};
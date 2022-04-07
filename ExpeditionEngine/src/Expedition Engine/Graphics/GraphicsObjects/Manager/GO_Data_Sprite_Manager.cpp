//#include "GO_Data_Sprite_Manager.h"
//
//#include "../../../../Expedition Resources/GraphicsResourcesSettings.h"
//
//GO_Data_Sprite_Manager::GO_Data_Sprite_Manager()
//	:dataPool(NumberOfGraphicsObjectsSprite)
//{
//}
//
//void GO_Data_Sprite_Manager::RegisterForDraw(PooledResourceIterator<GO_Data_Sprite>& iterator)
//{
//	activeData.PushBack(iterator);
//}
//
//void GO_Data_Sprite_Manager::DeregisterFromDraw(PooledResourceIterator<GO_Data_Sprite>& iterator)
//{
//	activeData.Remove(iterator);
//}
//
//void GO_Data_Sprite_Manager::Acquire(PooledResourceIterator<GO_Data_Sprite>& iterator, ID3D11Device* pDXDevice, GraphicsResourcesManager* pGraphicsResourcesManager, const SceneName& sceneToExistIn, SpriteData* pSpriteData, int numberOfInsts)
//{
//	dataPool.AcquireResource(iterator);
//	GO_Data_SpriteAttorney::ManagerControl::Initialize(iterator.GetCurrentObject(), pDXDevice, pGraphicsResourcesManager, sceneToExistIn, pSpriteData, numberOfInsts);
//}
//
//void GO_Data_Sprite_Manager::Acquire(PooledResourceIterator<GO_Data_Sprite>& iterator, ID3D11Device* pDXDevice, GraphicsResourcesManager* pGraphicsResourcesManager, const SceneName& sceneToExistIn, Image* pImage, Rect* pRect, int numberOfInsts)
//{
//	dataPool.AcquireResource(iterator);
//	GO_Data_SpriteAttorney::ManagerControl::Initialize(iterator.GetCurrentObject(), pDXDevice, pGraphicsResourcesManager, sceneToExistIn, pImage, pRect, numberOfInsts);
//}
//
//void GO_Data_Sprite_Manager::Release(PooledResourceIterator<GO_Data_Sprite>& iterator, GraphicsResourcesManager*& pGraphicsResourcesManager)
//{
//	GO_Data_SpriteAttorney::ManagerControl::Sanitize(iterator.GetCurrentObject(), pGraphicsResourcesManager);
//	dataPool.ReleaseResource(iterator);
//}
//
//void GO_Data_Sprite_Manager::Render(ID3D11Device*& pDXDevice, ID3D11DeviceContext*& pDXContext)
//{
//}
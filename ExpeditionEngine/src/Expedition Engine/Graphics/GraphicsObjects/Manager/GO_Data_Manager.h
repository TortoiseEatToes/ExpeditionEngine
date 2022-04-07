#pragma once


#include "../../../../Expedition Resources/SceneSettings.h"

#include "GO_Data_Color_Manager.h"
#include "GO_Data_ColorLight_Manager.h"
#include "GO_Data_Texture_Manager.h"
#include "GO_Data_TextureLight_Manager.h"
#include "../GO_Data_BaseAttorney.h"

class Model;
class TerrainModel;
class Model;
class SpriteData;
class Image;
class Rect;

class GraphicsResourcesManager;

class GO_Data_Manager
{
private:
	GO_Data_Color_Manager colorManager;
	GO_Data_ColorLight_Manager colorLightManager;
	//GO_Data_Sprite_Manager spriteManager;
	GO_Data_Texture_Manager textureManager;
	GO_Data_TextureLight_Manager textureLightManager;

	GraphicsResourcesManager* pGraphicsResourcesManager;

	ResourcePool<GO_Data_Base> dataPool;
	PooledResourceIterator<GO_Data_Base> currentIterator;

public:
	GO_Data_Manager();
	GO_Data_Manager(GO_Data_Manager&&) = delete;
	GO_Data_Manager(const GO_Data_Manager&) = delete;
	const GO_Data_Manager& operator = (GO_Data_Manager&&) = delete;
	const GO_Data_Manager& operator = (const GO_Data_Manager&) = delete;
	~GO_Data_Manager();

	void Initialize(GraphicsResourcesManager* pSceneGraphicsResourcesManager)
	{
		pGraphicsResourcesManager = pSceneGraphicsResourcesManager;
	}

	void Render_12(ID3D12GraphicsCommandList4* cmdList, ID3D12GraphicsCommandList4* shadowCmdList);

	//Acquire
	//void Acquire_12(PooledResourceIterator<GO_Data_Color>& iterator, Model* pModel, int numberOfInsts);
	//
	//void Acquire_12(PooledResourceIterator<GO_Data_ColorLight>& iterator, Model* pModel, int numberOfInsts);
	//void Acquire_12(PooledResourceIterator<GO_Data_ColorLight>& iterator, TerrainModel* pTerrainModel);
	//
	//void Acquire(PooledResourceIterator<GO_Data_Sprite>& iterator, const SceneName& sceneToExistIn, SpriteData* pSprite, int numberOfInsts);
	//void Acquire(PooledResourceIterator<GO_Data_Sprite>& iterator, const SceneName& sceneToExistIn, Image* pImage, Rect* pRect, int numberOfInsts);
	//
	//void Acquire(PooledResourceIterator<GO_Data_Texture>& iterator, Model* pModel, int numberOfInsts);
	//
	void Acquire_12(PooledResourceIterator<GO_Data_Base>& iterator, Model* mod, int numberOfInsts);
	void Acquire_12(PooledResourceIterator<GO_Data_Base>& iterator, TerrainModel* mod);

	//Release
	//void Release_12(PooledResourceIterator<GO_Data_Color>& iterator);
	//
	//void Release_12(PooledResourceIterator<GO_Data_ColorLight>& iterator);
	//
	//void Release(PooledResourceIterator<GO_Data_Sprite>& iterator);
	//void Release(PooledResourceIterator<GO_Data_Texture>& iterator);
	//
	void Release_12(PooledResourceIterator<GO_Data_Base>& iterator);

	//Register for Draw
	void RegisterForDrawColor(PooledResourceIterator<GO_Data_Base>& iterator);
	void RegisterForDrawColorLight(PooledResourceIterator<GO_Data_Base>& iterator);
	//void RegisterForDraw(PooledResourceIterator<GO_Data_Sprite>& iterator);
	void RegisterForDrawTexture(PooledResourceIterator<GO_Data_Base>& iterator);
	void RegisterForDrawTextureLight(PooledResourceIterator<GO_Data_Base>& iterator);

	//Deregister from Draw
	void DeregisterFromDrawColor(PooledResourceIterator<GO_Data_Base>& iterator);
	void DeregisterFromDrawColorLight(PooledResourceIterator<GO_Data_Base>& iterator);
	//void DeregisterFromDraw(PooledResourceIterator<GO_Data_Sprite>& iterator);
	void DeregisterFromDrawTexture(PooledResourceIterator<GO_Data_Base>& iterator);
	void DeregisterFromDrawTextureLight(PooledResourceIterator<GO_Data_Base>& iterator);
};
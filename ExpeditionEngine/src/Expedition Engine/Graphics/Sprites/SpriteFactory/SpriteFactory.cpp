#include "SpriteFactory.h"
#include"../SpriteData.h"

SpriteFactory* SpriteFactory::ptrInstance = nullptr;

SpriteFactory::SpriteFactory()
{
}


SpriteFactory::~SpriteFactory()
{
}

SpriteData* SpriteFactory::privCreateSprite(SceneName sceneToExistIn, Image* img) {

	SpriteData* b = pool_Sprite.GetPooledObject();

	b->Initialize(sceneToExistIn, img);

	return b;
}

void SpriteFactory::privRecycleSprite(SpriteData* b) {
	pool_Sprite.RecycleObject(b);
}

void SpriteFactory::Terminate() {
	Instance().pool_Sprite.DestroyAll();

	delete ptrInstance;
	ptrInstance = nullptr;
}
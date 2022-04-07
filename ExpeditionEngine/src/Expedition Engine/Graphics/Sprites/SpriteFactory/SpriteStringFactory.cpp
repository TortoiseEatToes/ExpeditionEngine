#include "SpriteStringFactory.h"
#include "../SpriteString.h"


SpriteStringFactory* SpriteStringFactory::ptrInstance = nullptr;

SpriteStringFactory::SpriteStringFactory()
{
}


SpriteStringFactory::~SpriteStringFactory()
{
}

SpriteString* SpriteStringFactory::privCreateSpriteString() {

	return pool_SpriteString.GetPooledObject();
}

void SpriteStringFactory::privRecycleSpriteString(SpriteString* b) {
	pool_SpriteString.RecycleObject(b);
}

void SpriteStringFactory::Terminate() {
	Instance().pool_SpriteString.DestroyAll();

	delete ptrInstance;
	ptrInstance = nullptr;
}
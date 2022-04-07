#ifndef SpriteFactory_h
#define SpriteFactory_h

#include "../../../Containers/Pool.h"

class SpriteData;
class Image;
enum SceneName;

class SpriteFactory
{

private:

	static SpriteFactory* ptrInstance;

	SpriteFactory();
	~SpriteFactory();
	SpriteFactory(const SpriteFactory&) = delete;
	SpriteFactory& operator = (const SpriteFactory&) = delete;

	static SpriteFactory& Instance() {
		if (!ptrInstance)
			ptrInstance = new SpriteFactory;
		return *ptrInstance;
	}

	Pool<SpriteData> pool_Sprite;

	SpriteData* privCreateSprite(SceneName sceneToExistIn, Image* img);
	void privRecycleSprite(SpriteData* b);

public:
	static SpriteData* CreateSprite(SceneName sceneToExistIn, Image* img) { return Instance().privCreateSprite(sceneToExistIn, img); }
	static void RecycleSprite(SpriteData* b) { Instance().privRecycleSprite(b); }

	static void Terminate();

};

#endif TankFactory_h


#ifndef SpriteStringFactory_h
#define SpriteStringFactory_h

#include "../../../Containers/Pool.h"

class SpriteString;


class SpriteStringFactory
{

private:

	static SpriteStringFactory* ptrInstance;

	SpriteStringFactory();
	~SpriteStringFactory();
	SpriteStringFactory(const SpriteStringFactory&) = delete;
	SpriteStringFactory& operator = (const SpriteStringFactory&) = delete;

	static SpriteStringFactory& Instance() {
		if (!ptrInstance)
			ptrInstance = new SpriteStringFactory;
		return *ptrInstance;
	}


	Pool<SpriteString> pool_SpriteString;

	SpriteString* privCreateSpriteString();
	void privRecycleSpriteString(SpriteString* b);

public:
	static SpriteString* CreateSpriteString() { return Instance().privCreateSpriteString(); }
	static void RecycleSpriteString(SpriteString* b) { Instance().privRecycleSpriteString(b); }

	static void Terminate();

};

#endif TankFactory_h


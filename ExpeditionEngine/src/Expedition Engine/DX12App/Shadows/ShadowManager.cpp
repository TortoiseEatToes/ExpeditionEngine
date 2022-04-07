#include "ShadowManager.h"

void ShadowManager::AddShadow(Shadow* inShadow)
{
	activeShadowList.PushFront(inShadow, inShadow->iterator);

	//inShadow->BuildResources();
}

void ShadowManager::RemoveShadow(Shadow* inShadow)
{
	activeShadowList.Remove(inShadow->iterator);
}

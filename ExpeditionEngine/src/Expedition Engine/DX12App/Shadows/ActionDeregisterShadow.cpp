#include "ActionDeregisterShadow.h"
#include "ShadowManager.h"
#include "../../GraphicsScene/GraphicsScene.h"
#include "../../Graphics/Light/LightManager.h"

const void ActionDeregisterShadow::Execute(GraphicsScene* pGS, Shadow* inShadow) const
{
	pGS->GetLightMgr()->GetShadowMgr()->RemoveShadow(inShadow);
}

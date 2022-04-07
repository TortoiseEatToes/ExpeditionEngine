#include "ActionRegisterShadow.h"
#include "ShadowManager.h"
#include "../../GraphicsScene/GraphicsScene.h"
#include "../../Graphics/Light/LightManager.h"

void const ActionRegisterShadow::Execute(GraphicsScene* pGS, Shadow* inShadow) const
{
	pGS->GetLightMgr()->GetShadowMgr()->AddShadow(inShadow);
}

#include "ShadowCmd.h"
#include "ShadowActionStrategy.h"
#include "Shadow.h"

void ShadowCmd::Initialize(const ShadowActionStrategy& inStrat, Shadow* inShadow)
{
	pAction = &inStrat;
	pShadow = inShadow;
}

void ShadowCmd::Execute(GraphicsScene* pScene)
{
	pAction->Execute(pScene, pShadow);
}

void ShadowCmd::RecycleCommand()
{
}

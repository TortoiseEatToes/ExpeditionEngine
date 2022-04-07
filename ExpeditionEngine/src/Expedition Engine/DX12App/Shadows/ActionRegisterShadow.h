#pragma once
#include "ShadowActionStrategy.h"

class ActionRegisterShadow : public ShadowActionStrategy
{
	// Inherited via ShadowActionStrategy
	virtual const void Execute(GraphicsScene* pGS, Shadow* inShadow) const override;
};


#pragma once

#include "../../GraphicsScene/Commands/GraphicsSceneCommand.h"

class ShadowActionStrategy;
class Shadow;

class ShadowCmd : public GraphicsSceneCommand
{
public:
	ShadowCmd() = default;

	ShadowCmd(ShadowCmd&&) = delete;
	ShadowCmd(const ShadowCmd&) = delete;
	const ShadowCmd& operator = (ShadowCmd&&) = delete;
	const ShadowCmd& operator = (const ShadowCmd&) = delete;

	~ShadowCmd() = default;

	void Initialize(const ShadowActionStrategy& inStrat, Shadow* inShadow);

	// Inherited via GraphicsSceneCommand
	virtual void Execute(GraphicsScene* pScene) override;

	virtual void RecycleCommand() override;

private:
	const ShadowActionStrategy* pAction;
	Shadow* pShadow;
};


#pragma once

class Shadow;
class ShadowManager;
class GraphicsScene;

class ShadowActionStrategy
{
public:
	ShadowActionStrategy() = default;


	ShadowActionStrategy(ShadowActionStrategy&&) = delete;
	ShadowActionStrategy(const ShadowActionStrategy&) = delete;
	const ShadowActionStrategy& operator = (ShadowActionStrategy&&) = delete;
	const ShadowActionStrategy& operator = (const ShadowActionStrategy&) = delete;

	virtual ~ShadowActionStrategy() = default;

	virtual const void Execute(GraphicsScene* pGS,  Shadow* inShadow) const = 0;
};

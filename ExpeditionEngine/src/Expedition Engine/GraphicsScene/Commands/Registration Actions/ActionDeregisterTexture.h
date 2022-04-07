#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionDeregisterTexture : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionDeregisterTexture() = default;
	ActionDeregisterTexture(ActionDeregisterTexture&& other) = delete;
	ActionDeregisterTexture(const ActionDeregisterTexture& other) = delete;
	ActionDeregisterTexture& operator= (ActionDeregisterTexture&& other) = delete;
	ActionDeregisterTexture& operator= (const ActionDeregisterTexture& other) = delete;
	~ActionDeregisterTexture() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

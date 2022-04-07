#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionDeregisterTextureLight : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionDeregisterTextureLight() = default;
	ActionDeregisterTextureLight(ActionDeregisterTextureLight&& other) = delete;
	ActionDeregisterTextureLight(const ActionDeregisterTextureLight& other) = delete;
	ActionDeregisterTextureLight& operator= (ActionDeregisterTextureLight&& other) = delete;
	ActionDeregisterTextureLight& operator= (const ActionDeregisterTextureLight& other) = delete;
	~ActionDeregisterTextureLight() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};


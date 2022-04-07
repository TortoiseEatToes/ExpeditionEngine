#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionRegisterTextureLight : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionRegisterTextureLight() = default;
	ActionRegisterTextureLight(ActionRegisterTextureLight&& other) = delete;
	ActionRegisterTextureLight(const ActionRegisterTextureLight& other) = delete;
	ActionRegisterTextureLight& operator= (ActionRegisterTextureLight&& other) = delete;
	ActionRegisterTextureLight& operator= (const ActionRegisterTextureLight& other) = delete;
	~ActionRegisterTextureLight() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

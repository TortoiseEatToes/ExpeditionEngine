#pragma once
#include "GraphicsObjectRegistrationActionStrategy.h"

class ActionRegisterTexture : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionRegisterTexture() = default;
	ActionRegisterTexture(ActionRegisterTexture&& other) = delete;
	ActionRegisterTexture(const ActionRegisterTexture& other) = delete;
	ActionRegisterTexture& operator= (ActionRegisterTexture&& other) = delete;
	ActionRegisterTexture& operator= (const ActionRegisterTexture& other) = delete;
	~ActionRegisterTexture() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

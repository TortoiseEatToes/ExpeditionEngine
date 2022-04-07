#pragma once

#include "../../Expedition Engine/Game Object/GameObject.h"
#include "../Inputs/PlayerControllerSwapToLayer1.h"

class GraphicObject_Sprite;

class SpriteController : public GameObject {

public:
	SpriteController() = delete;
	SpriteController(const SceneName& startingScene);
	SpriteController(SpriteController&&) = delete;
	SpriteController(const SpriteController&) = delete;
	const SpriteController& operator =(SpriteController&&) = delete;
	const SpriteController& operator =(const SpriteController&) = delete;
	~SpriteController();

	void OnSceneEnter() override;
	void OnSceneExit() override;

private:
	PlayerControllerSwapToLayer1 playerControllerSwap1;
	PlayerControllerSwapToLayer1 playerControllerSwap2;
	PlayerControllerSwapToLayer1 playerControllerSwap3;
	PlayerControllerSwapToLayer1 playerControllerSwap4;
	PlayerControllerSwapToLayer1 playerControllerSwap5;

	GraphicsObject_Sprite* pSprite1;
	GraphicsObject_Sprite* pSprite2;
	GraphicsObject_Sprite* pSprite3;
	GraphicsObject_Sprite* pSprite4;
	GraphicsObject_Sprite* pSprite5;

};
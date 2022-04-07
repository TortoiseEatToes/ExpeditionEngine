#pragma once

#include "../../Expedition Engine/Game Object/GameObject.h"
#include "../Inputs/ControlSchemeSwitcher.h"
#include "../Inputs/InputableTestJumping.h"
#include "../Inputs/PlayerControllerMoveBackward.h"
#include "../Inputs/PlayerControllerMoveForward.h"
#include "../Inputs/PlayerControllerMoveLeft.h"
#include "../Inputs/PlayerControllerMoveRight.h"
#include "../Inputs/PlayerControllerQuitGame.h"



//class GraphicsObject_Color;
//class GraphicsObject_ColorLight;
//class GraphicsObject_Texture;
//class GraphicsObject_TextureLight;
//class GraphicsObject_Sprite;
class SpriteString;

class PlayerController : public GameObject
{
public:
	PlayerController() = delete;
	PlayerController(const SceneName& startingScene);
	PlayerController(const PlayerController& other) = delete;
	PlayerController& operator= (const PlayerController& other) = delete;
	~PlayerController();

	void OnSceneEnter() override;
	void OnSceneExit() override;

private:

	const static int sideLen = 25;

	GraphicsObject_ColorLight* testInstanced;
	GraphicsObject_ColorLight* testNoInstance[sideLen*sideLen*sideLen];

	GraphicsObject_Sprite* pSprite;

	SpriteString* spriteString;

	GraphicsObject_ColorLight* testBox;
	GraphicsObject_ColorLight* testSphere;
	GraphicsObject_TextureLight* testTank;
	GraphicsObject_TextureLight* terrain;
	GraphicsObject_Texture* skyBox;

	ControlSchemeSwitcher controlSchemeSwitcher;
	InputComponentTestJumping inputComponentTestJumping;
	PlayerControllerMoveBackward playerControllerMoveBackward;
	PlayerControllerMoveForward playerControllerMoveForward;
	PlayerControllerMoveLeft playerControllerMoveLeft;
	PlayerControllerMoveRight playerControllerMoveRight;
	PlayerControllerQuitGame playerControllerQuitGame;
};
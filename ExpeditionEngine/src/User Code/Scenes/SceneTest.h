#pragma once

#include "../../Expedition Engine/Scenes/Scene.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject.h"
#include "../Demo1/CameraController/CameraController.h"
#include "../Demo1/Planes/PlaneController.h"
#include "../Demo1/BouncyBalls/BallManager.h"
#include "../Inputs/SceneSwapper.h"

#include "../../Expedition Engine/Graphics/Sprites/SpriteString.h"

#include "../Button/SceneSwapperButton.h"

class SceneTest : public Scene, public Align16
{
public:
	SceneTest();
	SceneTest(const SceneTest& other) = delete;
	SceneTest& operator= (const SceneTest& other) = delete;
	~SceneTest();

	void SceneInitialize() override;
	void SceneStart() override;
	void SceneStop() override;
	void SceneShutDown() override;

	PlaneController& GetPlaneController() 
	{
		return planeController;
	}

private:
	SceneSwapper sceneSwapper;
	//SceneSwapper sceneSwapper2;

	CameraController cameraController;
	PlaneController planeController;
	BallManager ballManager;

	//SpriteString spriteString;

	//SceneSwapperButton sceneSwapperButton;
};

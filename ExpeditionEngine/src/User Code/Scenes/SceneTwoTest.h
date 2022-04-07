#pragma once

#include "../../Expedition Engine/Scenes/Scene.h"

#include "../Game Objects/SpriteController.h"

#include "../Inputs/SceneSwapper.h"

#include "../Demo1/CameraController/CameraController.h"

#include "../../Expedition Engine/Graphics/ParticleSystem/ParticleEmitter.h"
#include "../Button/ParticleTypeSwapperButton.h"

class Camera;
class GraphicsObject_Color;
class GraphicsObject_TextureLight;
class GraphicsObject_ColorLight;

class SceneTwoTest : public Scene, public Align16
{
public:
	SceneTwoTest();
	SceneTwoTest(const SceneTwoTest& other) = delete;
	SceneTwoTest& operator= (const SceneTwoTest& other) = delete;
	~SceneTwoTest();

	void SceneInitialize() override;
	void SceneStart() override;
	void SceneStop() override;
	void SceneShutDown() override;

private:
	//PlayerController playerController;
	ParticleEmitter pe;
	SceneSwapper sceneSwapper;
	SceneSwapper sceneSwapper2;
	SpriteController spriteController;
	ParticleTypeSwapperButton particleSwapper;

	GraphicsObject_ColorLight* terrain;

	CameraController cameraController;
	//GraphicObject_Color* testBox;
	//GraphicObject_Color* testBox1;
	//GraphicObject_Color* testBox2;
	//GraphicObject_Color* testBox3;
	//GraphicObject_Color* testBox4;
};
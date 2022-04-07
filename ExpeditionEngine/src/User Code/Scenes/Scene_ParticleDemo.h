#pragma once

#include "../../Expedition Engine/Scenes/Scene.h"
#include "../Inputs/SceneSwapper.h"
#include "../../Expedition Engine/Scene Components/Particle Emitter/ParticleEmitter.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject.h"
#include "../Demo1/CameraController/CameraController.h"
#include "../../Expedition Engine/Scene Components/Audio Emitter/AudioEmitter.h"

class Scene_ParticleDemo : public Scene
{
public:
	Scene_ParticleDemo();
	Scene_ParticleDemo(const Scene_ParticleDemo& other) = delete;
	Scene_ParticleDemo& operator= (const Scene_ParticleDemo& other) = delete;
	~Scene_ParticleDemo();

	void SceneInitialize() override;
	void SceneStart() override;
	void SceneStop() override;
	void SceneShutDown() override;

private:
	SceneSwapper sceneSwapper;
	SceneSwapper sceneSwapper2;
	ParticleEmitter particleEmitterFire;
	ParticleEmitter particleEmitterWater;
	ParticleEmitter particleEmitterEarth;
	ParticleEmitter particleEmitterAir;

	GraphicsObject go_Vases;
	GraphicsObject go_Sky;
	GraphicsObject go_Plane;
	GraphicsObject go_Terrain;
	CameraController camControl;
	AudioEmitter musicEmitter;
};

#pragma once

#include "../../Expedition Engine/Scenes/Scene.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject.h"
#include "../../Expedition Engine/Containers/List.h"
#include "../../Expedition Engine/Math/Matrix/Matrix4F.h"
#include "../../Expedition Engine/Scene Components/Audio Emitter/AudioEmitter.h"

#include "../../Expedition Engine/Scene Components/Particle Emitter/ParticleEmitter.h"

#include "../Demo1/CameraController/CameraController.h"

#include "Forest_Camera.h"
#include "Footstep_Controller.h"

class Scene_ForestDemo : public Scene, public Align16
{
public:
	Scene_ForestDemo();
	~Scene_ForestDemo();

	Scene_ForestDemo(Scene_ForestDemo&&) = delete;
	Scene_ForestDemo(const Scene_ForestDemo&) = delete;
	const Scene_ForestDemo operator = (Scene_ForestDemo&&) = delete;
	const Scene_ForestDemo operator = (const Scene_ForestDemo&) = delete;


	void SceneInitialize() override;
	void SceneStart() override;
	void SceneStop() override;
	void SceneShutDown() override;

private:

	//CameraController camController;

	Forest_Camera cam;

	GraphicsObject* pgo_Trees;
	List<Vector4F*> list_vWorldPos;

	GraphicsObject go_Terrain;
	GraphicsObject go_SkyBox;

	AudioEmitter musicEmitter;
	GraphicsObject go_CampFires;

	ParticleEmitter fireParticles;
	Footstep_Controller footsteps;

	static const int lengthOfTreeArea = 10000;

	static const int sizeOfTreeSpot = 200;

	static const int treeSpotsPerSide = lengthOfTreeArea / sizeOfTreeSpot;

	static const int chanceOfTreeSpawnNumerator = 2;
	static const int chanceOfTreeSpawnDenominator = 10;

};


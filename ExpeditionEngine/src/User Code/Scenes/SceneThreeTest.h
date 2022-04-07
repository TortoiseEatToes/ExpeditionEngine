#pragma once

#include "../../Expedition Engine/Scenes/Scene.h"

//#include "../Game Objects/PlayerController.h"

#include "../Inputs/SceneSwapper.h"
#include "../Alarm/RandomColorAlarm.h"

#include "../../Expedition Engine/Graphics/ParticleSystem/ParticleEmitter.h"

class Camera;
class GraphicsObject_Color;

class SceneThreeTest : public Scene, public Align16
{
public:
	SceneThreeTest();
	SceneThreeTest(const SceneThreeTest& other) = delete;
	SceneThreeTest& operator= (const SceneThreeTest& other) = delete;
	~SceneThreeTest();

	void SceneInitialize() override;
	void SceneStart() override;
	void SceneStop() override;
	void SceneShutDown() override;

private:
	ParticleEmitter partEmitter;
	SceneSwapper sceneSwapper;
	SceneSwapper sceneSwapper2;
	RandomColorAlarm randomColorAlarm;
	//GraphicsObject_Color* pColorChangingSphere;
	const float secondsBetweenSphereColorChange = 0.5f;
};
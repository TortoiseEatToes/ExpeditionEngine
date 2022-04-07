#pragma once

#include "../../../Expedition Engine/Scenes/Scene.h"

#include "../../Game Objects/PlayerController.h"
#include "../../Demo1/CameraController/CameraController.h"

class PlanetOneScene : public Scene, public Align16
{
public:
	PlanetOneScene();
	PlanetOneScene(PlanetOneScene&&) = delete;
	PlanetOneScene(const PlanetOneScene&) = delete;
	const PlanetOneScene& operator = (PlanetOneScene&&) = delete;
	const PlanetOneScene& operator = (const PlanetOneScene&) = delete;
	~PlanetOneScene();

	void SceneInitialize() override;
	void SceneStart() override;
	void SceneStop() override;
	void SceneShutDown() override;

private:
	PlayerController player;
	CameraController camera;
};


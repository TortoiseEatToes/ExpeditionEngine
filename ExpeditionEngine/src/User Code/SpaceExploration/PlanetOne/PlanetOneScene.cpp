#include "PlanetOneScene.h"

PlanetOneScene::PlanetOneScene() : Scene(ScenePlanet1),player(ScenePlanet1), camera(ScenePlanet1)
{
}

PlanetOneScene::~PlanetOneScene()
{
}

void PlanetOneScene::SceneInitialize()
{
}

void PlanetOneScene::SceneStart()
{
	player.EnterScene(ScenePlanet1);
	camera.EnterScene(ScenePlanet1);
}

void PlanetOneScene::SceneStop()
{
	player.ExitScene();
	camera.ExitScene();
}

void PlanetOneScene::SceneShutDown()
{
}

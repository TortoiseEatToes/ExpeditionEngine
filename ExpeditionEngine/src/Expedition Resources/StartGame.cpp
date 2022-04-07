#include "../Expedition Engine/Engine/ExpeditionEngine.h"

#include "../Expedition Engine/Scenes/SceneManager.h"

#include "../User Code/Scenes/SceneTest.h"
#include "../User Code/Scenes/Scene_ParticleDemo.h"
#include "../User Code/ForestDemo/Scene_ForestDemo.h"
//#include "../User Code/Scenes/SceneTwoTest.h"
//#include "../User Code/Scenes/SceneThreeTest.h"
//#include "../User Code/SpaceExploration/PlanetOne/PlanetOneScene.h"

//This is the second function called by the ExpeditionEngine during the engine start up.  Use this to create all of the memory you need for your game.
void ExpeditionEngine::StartGame()
{
	//SceneManager::CreateScene<Scene_ParticleDemo>(SceneName::Scene1);
	//SceneManager::CreateScene<Scene_ForestDemo>(SceneName::SceneForest);
	SceneManager::CreateScene<SceneTest>(SceneName::BouncyBalls);
	SceneManager::CreateScene<Scene_ForestDemo>(SceneName::SceneForest);
	


	//SceneManager::CreateScene<SceneTest>(SceneName::Scene1);
	//SceneManager::CreateScene<SceneTwoTest>(SceneName::Scene2);
	//SceneManager::CreateScene<SceneThreeTest>(SceneName::Scene3);
	//SceneManager::CreateScene<PlanetOneScene>(SceneName::ScenePlanet1);
}
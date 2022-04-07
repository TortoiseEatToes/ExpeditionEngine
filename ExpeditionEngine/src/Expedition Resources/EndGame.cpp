#include "../Expedition Engine/Engine/ExpeditionEngine.h"

#include "../Expedition Engine/Scenes/SceneManager.h"

//This is called once as the engine is shuttng down.
//Use this to clean up any memory that was cleaned up over the course of the game.
void ExpeditionEngine::EndGame()
{
    SceneManager::DestroyScene(SceneName::SceneForest);
    SceneManager::DestroyScene(SceneName::BouncyBalls);
    //SceneManager::DestroyScene(SceneName::Scene2);
    //SceneManager::DestroyScene(SceneName::Scene3);
    //SceneManager::DestroyScene(SceneName::ScenePlanet1);
}
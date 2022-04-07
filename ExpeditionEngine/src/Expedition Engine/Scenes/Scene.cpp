#include "Scene.h"

#include "Commands/SceneCommand.h"
#include "SceneManagerAttorney.h"

#include "../Scene Components/Input/Manager/InputManagerAttorney.h"
#include "../Scene Components/Collision/Manager/CollisionSystemAttorney.h"

#include "../Time/SceneTimeManagerAttorney.h"

Scene::Scene(const SceneName& startingSceneName)
{
	sceneName = startingSceneName;
}

const SceneTimeManager & Scene::GetTimeManager() const
{
	return pEngineScene->GetTimeManager();
}

void Scene::SetCurrentPerspectiveCamera(Camera * const pCamera)
{
	pEngineScene->GetCameraManager().SetPerspectiveCamera(pCamera);
}

void Scene::SetCurrentOrthographicCamera(Camera * const pCamera)
{
	pEngineScene->GetCameraManager().SetOrthographicCamera(pCamera);
}

Camera * const Scene::GetCurrentPerspectiveCamera()
{
	return pEngineScene->GetCameraManager().GetPerspectiveCamera();
}

Camera * const Scene::GetCurrentOrthographicCamera()
{
	return pEngineScene->GetCameraManager().GetOrthographicCamera();
}

void Scene::EngineIntitialization(EngineScene * const pInitEngineScene)
{
	pEngineScene = pInitEngineScene;
}
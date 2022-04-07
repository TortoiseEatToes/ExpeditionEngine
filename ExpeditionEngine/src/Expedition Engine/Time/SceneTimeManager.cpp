#include "SceneTimeManager.h"

SceneTimeManager::SceneTimeManager()
{
}

void SceneTimeManager::ProcessTime()
{
	deltaTime = stopwatch.Stop();

	previousTime = currentTime;

	currentTime = previousTime + deltaTime;

	stopwatch.Start();
}

void SceneTimeManager::StartTime()
{
	stopwatch.Start();
}

void SceneTimeManager::StopTime()
{
	stopwatch.Stop();
}

const float& SceneTimeManager::GetCurrentSceneTime() const
{
	return currentTime;
}

const float& SceneTimeManager::GetDeltaTime() const
{
	return deltaTime;
}

SceneTimeManager::~SceneTimeManager()
{

}
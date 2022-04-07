#pragma once
#include "Scene.h"

class SceneAttorney
{
public:
	class EngineSceneControls
	{
	private:
		friend class EngineScene;

		static void EngineIntitialization(Scene * const pScene, EngineScene * const pInitEngineScene)
		{
			pScene->EngineIntitialization(pInitEngineScene);
		}

		static void SceneInitialize(Scene * const pScene)
		{
			pScene->SceneInitialize();
		}

		static void SceneStart(Scene * const pScene)
		{
			pScene->SceneStart();
		}

		static void SceneStop(Scene * const pScene)
		{
			pScene->SceneStop();
		}

		static void SceneShutDown(Scene * const pScene)
		{
			pScene->SceneShutDown();
		}
	};
};
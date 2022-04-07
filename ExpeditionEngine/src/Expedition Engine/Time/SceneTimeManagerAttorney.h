#ifndef SCENETIMEATTORNEY_H
#define SCENETIMEATTORNEY_H

#include "SceneTimeManager.h"

class SceneTimeManagerAttorney
{
public:

	class SceneControl
	{
	private:
		friend class EngineScene;

		static void ProcessTime(SceneTimeManager& pScene)
		{
			pScene.ProcessTime();
		}

		static void StartTime(SceneTimeManager& pScene)
		{
			pScene.StartTime();
		}

		static void StopTime(SceneTimeManager& pScene)
		{
			pScene.StopTime();
		}
	};
};

#endif // !ENGINETIMEATTORNEY_H
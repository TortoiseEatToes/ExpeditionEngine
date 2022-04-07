#pragma once

#include "SceneComponent.h"

class SceneComponentAttorney
{
public:
	struct CommandControl
	{
	private:
		friend class ActionRegisterSceneComponent;
		friend class ActionDeregisterSceneComponent;

		static void RegisterIntoScene(SceneComponent* pComponent, EngineScene& engineScene)
		{
			pComponent->cmdRegisterIntoScene(engineScene);
		}

		static void DeregisterFromScene(SceneComponent* pComponent, EngineScene& engineScene)
		{
			pComponent->cmdDeregisterFromScene(engineScene);
		}
	};
};
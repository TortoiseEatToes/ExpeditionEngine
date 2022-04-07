#include "SceneDeletionCommand.h"
#include "../../SceneManagerAttorney.h"

void SceneDeletionCommand::Execute()
{
	SceneManagerAttorney::ManagerCommandControl::DestroyScene(sceneName);
}